// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/Component/SlidingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USlidingComponent::USlidingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ScaleCapsuleTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("ScaleCapsuleTimeline")); 
	{
		static ConstructorHelpers::FObjectFinder<UCurveFloat> ObjectFinder(TEXT("/Script/Engine.CurveFloat'/Game/Blueprints/Curves/Curve_CapsuleScale.Curve_CapsuleScale'"));
		ensure(ObjectFinder.Object); 

		FOnTimelineFloat Delegate; 
		Delegate.BindUFunction(this, TEXT("ScaleCapsule"));
		ScaleCapsuleTimeline->AddInterpFloat(ObjectFinder.Object, Delegate); 
	}

	ResetSlideRotation = CreateDefaultSubobject<UTimelineComponent>(TEXT("ResetSlideRotation"));
	{
		static ConstructorHelpers::FObjectFinder<UCurveFloat> ObjectFinder(TEXT("/Script/Engine.CurveFloat'/Game/Blueprints/Curves/Curve_InterpRotation.Curve_InterpRotation'"));
		ensure(ObjectFinder.Object); 

		FOnTimelineFloat Delegate; 
		Delegate.BindUFunction(this, TEXT("ResetXYRotation")); 
		ResetSlideRotation->AddInterpFloat(ObjectFinder.Object, Delegate); 

		FScriptDelegate FinishedDelegate;
		FinishedDelegate.BindUFunction(this, TEXT("ResetWalkMaxSpeedAndAccel"));
		ResetSlideRotation->SetTimelineFinishedFunc(FOnTimelineEvent(FinishedDelegate));
	}


	SlidingMontage = CreateDefaultSubobject<UAnimMontage>(TEXT("SlidingMontage")); 
	{
		static ConstructorHelpers::FObjectFinder<UAnimMontage> ObjectFinder(TEXT("/Script/Engine.AnimMontage'/Game/Parkour/Sliding/Animations/Sliding_Montage.Sliding_Montage'"));
		ensure(ObjectFinder.Object); 
	}
	
	SlidingEndMontage = CreateDefaultSubobject<UAnimMontage>(TEXT("SlidingEndMontage"));
	{
		static ConstructorHelpers::FObjectFinder<UAnimMontage> ObjectFinder(TEXT("/Script/Engine.AnimMontage'/Game/Parkour/Sliding/Animations/SlidingEnd_Montage.SlidingEnd_Montage'"));
		ensure(ObjectFinder.Object);
	}
}


// Called when the game starts
void USlidingComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner(); 
	ensure(Owner); 

	CharMoveComp = Cast<UCharacterMovementComponent>(Owner->GetComponentByClass(UCharacterMovementComponent::StaticClass())); 
	ensure(CharMoveComp); 

	CharMesh = Cast<USkeletalMeshComponent>(Owner->GetComponentByClass(USkeletalMeshComponent::StaticClass())); 
	ensure(CharMesh); 

	CapsuleComp = Cast<UCapsuleComponent>(Owner->GetComponentByClass(UCapsuleComponent::StaticClass())); 
	ensure(CapsuleComp); 

}


// Called every frame
void USlidingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USlidingComponent::Slide(const FInputActionValue& Value)
{	
	if (CharMoveComp->Velocity.Size() > 200.)
	{
		if (CharMesh->GetAnimInstance()->IsAnyMontagePlaying() && CharMoveComp->IsFalling())
		{
			return;
		}

		IsSliding = true; 

		CharMesh->GetAnimInstance()->Montage_Play(SlidingMontage); 

		ScaleCapsuleTimeline->PlayFromStart(); 

		FTimerDynamicDelegate TraceFloorDelegate; 
		FTimerHandle SlideTraceHandle = UKismetSystemLibrary::K2_SetTimerDelegate(TraceFloorDelegate, 0.01, true); 

		CheckIfOnFloor(4.0, 18.0, 0.2); 

		if (SlideTraceHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(SlideTraceHandle); 
		}

	}

	

}

void USlidingComponent::RevertCapsule()
{
	if (CharMoveComp->IsCrouching()) { return; }

	ScaleCapsuleTimeline->Reverse(); 

}

void USlidingComponent::ScaleCapsule(float Value)
{
	double HalfHeight = UKismetMathLibrary::Lerp(90., 35., Value); 
	CapsuleComp->SetCapsuleHalfHeight(HalfHeight, true); 

	FVector NewLocation = UKismetMathLibrary::VLerp(FVector(0., 0., -90.), FVector(0., 0., -35.), Value); 
	CharMesh->SetRelativeLocation(NewLocation); 
}

void USlidingComponent::CheckIfOnFloor(float TraceRadius, float TraceHalfHeight, float MontageBlendOutTime)
{
	FVector MeshLocation = CharMesh->GetComponentLocation();

	TArray<AActor*> IgnoreActors;
	FHitResult HitResult;

	bool Hit = UKismetSystemLibrary::CapsuleTraceSingle(Owner, MeshLocation, MeshLocation,
		TraceRadius, TraceHalfHeight, ETraceTypeQuery::TraceTypeQuery1, false, IgnoreActors, EDrawDebugTrace::None, HitResult, true);

	if (!Hit)
	{
		IsSliding = false;
		CharMesh->GetAnimInstance()->Montage_Stop(MontageBlendOutTime);
	}
}

// To be implemented
// abp_manny에서 anim notify와 연관되어 check should continue sliding이 호출
void USlidingComponent::CheckShouldContinueSliding(FTimerHandle SlideTraceHandle)
{
	if (IsSliding)
	{
		if (FindCurrentFloorAngleAndDirection().IsSlopeUp)
		{
			CharMoveComp->Velocity = CurrentSlidingVelocity; 
			FTimerHandle ContinueSlidingHandle = UKismetSystemLibrary::K2_SetTimer(this, TEXT("ContinueSliding"), 0.001, true); 
			CurrentAngle = FindCurrentFloorAngleAndDirection().Angle;
		}
		else
		{
			PlayGetUpAnimation(SlideTraceHandle);

		}

	}
}

void USlidingComponent::ContinueSliding(FTimerHandle SlidingTraceHandle, FTimerHandle ContinueSlidingHandle)
{
	CurrentAngle = FindCurrentFloorAngleAndDirection().Angle;
	double InterpAngle = FMath::FInterpTo(CurrentAngle, FindCurrentFloorAngleAndDirection().Angle, UGameplayStatics::GetWorldDeltaSeconds(Owner), 0.4);

	if (InterpAngle < 3.)
	{
		if (CharMoveComp->Velocity.Size() < SpeedToStopSliding)
		{
			if (ContinueSlidingHandle.IsValid())
			{
				GetWorld()->GetTimerManager().ClearTimer(ContinueSlidingHandle); 
			}

			PlayGetUpAnimation(SlidingTraceHandle); 

		}
	}
	else
	{
		FVector WorldDirection = FRotator(0., Owner->GetActorRotation().Yaw, 0.).Vector(); 
		APawn* OwnerPawn = Cast<APawn>(Owner); 
		OwnerPawn->AddMovementInput(WorldDirection); 
		
		CharMoveComp->MaxWalkSpeed = 1500.; 
		CharMoveComp->MaxAcceleration = 500.; 

		if (CheckIfHitSurface(0., 20., 80., EDrawDebugTrace::None))
		{
			if (ContinueSlidingHandle.IsValid())
			{
				GetWorld()->GetTimerManager().ClearTimer(ContinueSlidingHandle);
			}

			PlayGetUpAnimation(SlidingTraceHandle); 
		}
	}

}

FAngleDirectionStruct USlidingComponent::FindCurrentFloorAngleAndDirection()
{
	const FVector& FloorNormal = CharMoveComp->CurrentFloor.HitResult.Normal;
	double Angle = UKismetMathLibrary::DegAcos(FVector::DotProduct(FloorNormal, FVector(0., 0., 1.)));

	FRotator SlopeMatrix = FRotationMatrix::MakeFromXY(FloorNormal, Owner->GetActorForwardVector()).Rotator();

	bool IsSlopeUp; 

	if (SlopeMatrix.Pitch * SlopeMatrix.Roll > 0.)
	{
		IsSlopeUp = true; 
	}
	else
	{
		IsSlopeUp = false; 
	}

	return FAngleDirectionStruct(Angle, IsSlopeUp);
}

void USlidingComponent::PlayGetUpAnimation(FTimerHandle SlideTraceHandle)
{
	CharMesh->GetAnimInstance()->Montage_Play(SlidingEndMontage);

	FTimerHandle GetupTimerHandle; 

	GetWorld()->GetTimerManager().SetTimer(GetupTimerHandle, [&]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Delay executed and player will be get up"));
		}, 0.05, false);

	if (SlideTraceHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(SlideTraceHandle);
	}

	RevertCapsule(); 

	ResetSlideRotation->PlayFromStart(); 

}

void USlidingComponent::ResetXYRotation(float Value)
{
	DefaultYawRotation = FRotator(0., Owner->GetActorRotation().Yaw, 0.); 

	FRotator NewRotation = UKismetMathLibrary::RLerp(Owner->GetActorRotation(), DefaultYawRotation, Value, false);

	Owner->SetActorRotation(NewRotation); 

}

void USlidingComponent::ResetWalkMaxSpeedAndAccel()
{
	CharMoveComp->MaxWalkSpeed = 500.;
	CharMoveComp->MaxAcceleration = 1500.; 
}

bool USlidingComponent::CheckIfHitSurface(float TraceZOffset, float Radius, float CompareAngle, EDrawDebugTrace::Type DrawDebugType)
{
	FVector SocketLocation = CharMesh->GetSocketLocation(TEXT("foot_l")); 
	FVector AddedLocation = SocketLocation + FVector(0., 0., TraceZOffset); 

	TArray<AActor*> IgnoreActors; 

	IgnoreActors.Add(CharMoveComp->CurrentFloor.HitResult.GetActor()); 


	FHitResult HitResult;

	const bool Hit = UKismetSystemLibrary::SphereTraceSingle(Owner, AddedLocation, AddedLocation, Radius, 
		ETraceTypeQuery::TraceTypeQuery1, false, IgnoreActors, DrawDebugType, HitResult, true);

	if (Hit)
	{
		float SlideAngle = FMath::Abs(UKismetMathLibrary::DegAcos(FVector::DotProduct(HitResult.Normal, FVector(0., 0., 1.))));
		if (SlideAngle > CompareAngle)
		{
			return true; 
		}
		else
		{
			return false; 
		}
	}

	
}







