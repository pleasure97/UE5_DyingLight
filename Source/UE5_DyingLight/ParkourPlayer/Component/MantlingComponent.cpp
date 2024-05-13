// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/Component/MantlingComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UMantlingComponent::UMantlingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MantlingMontage = CreateDefaultSubobject<UAnimMontage>(TEXT("MantlingMontage")); 
	{
		static ConstructorHelpers::FObjectFinder<UAnimMontage> ObjectFinder(TEXT("/Script/Engine.AnimMontage'/Game/Parkour/Mantling/Animations/Mantle_UE_Montage.Mantle_UE_Montage'"));
		ensure(ObjectFinder.Object); 
	}


}


// Called when the game starts
void UMantlingComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner(); 
	ensure(Owner); 

	CharMoveComp = Cast<UCharacterMovementComponent>(Owner->GetComponentByClass(UCharacterMovementComponent::StaticClass())); 
	ensure(CharMoveComp); 

	MotionWarping = Cast<UMotionWarpingComponent>(Owner->GetComponentByClass(UMotionWarpingComponent::StaticClass())); 
	ensure(MotionWarping); 

	CharMesh = Cast<USkeletalMeshComponent>(Owner->GetComponentByClass(USkeletalMeshComponent::StaticClass())); 
	ensure(CharMesh);
	
}


// Called every frame
void UMantlingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMantlingComponent::Mantle(const FInputActionValue& Value)
{
	FMantlePosStruct MantlePositons = TraceMantle(120., 200., 0.5);	

	if (CanMantle)
	{
		PlayMantle(MantlePositons.MantlePos1, MantlePositons.MantlePos2, -100., 30., 1.);
	}
	else
	{
		ACharacter* OwnerCharacter = Cast<ACharacter>(Owner); 
		OwnerCharacter->Jump(); 
	}
}

FMantlePosStruct UMantlingComponent::TraceMantle(float InitialTraceLength, float SecondaryTraceZOffset, float FallingHeightMultiplier)
{
	CanMantle = false; 

	FVector LineStart = Owner->GetActorLocation(); 
	FVector LineEnd = LineStart + Owner->GetActorForwardVector() * InitialTraceLength; 

	TArray<AActor*> IgnoreLineActors; 
	FHitResult LineHitResult;

	const bool LineHit = UKismetSystemLibrary::LineTraceSingle(Owner, LineStart, LineEnd, 
		ETraceTypeQuery::TraceTypeQuery1, false, IgnoreLineActors, EDrawDebugTrace::None, LineHitResult, true); 

	if (LineHit)
	{
		FVector FirstSphereEnd = LineHitResult.Location;

		float FallingCoefficient = UKismetMathLibrary::SelectFloat(FallingHeightMultiplier, 1., CharMoveComp->IsFalling());

		FVector FirstSphereStart = FirstSphereEnd + FVector(0., 0., SecondaryTraceZOffset * FallingCoefficient);

		TArray<AActor*> IgnoreSphereActors; 
		FHitResult FirstSphereHitResult; 

		const bool FirstSphereHit = 
			UKismetSystemLibrary::SphereTraceSingle(Owner, FirstSphereStart, FirstSphereEnd, 10., 
				ETraceTypeQuery::TraceTypeQuery1, false, IgnoreSphereActors, EDrawDebugTrace::None, FirstSphereHitResult, true);

		if (FirstSphereHit)
		{
			FVector MantlePos1 = FirstSphereHitResult.ImpactPoint + Owner->GetActorForwardVector() * -50.;
			FVector MantlePos2 = FirstSphereHitResult.ImpactPoint + Owner->GetActorForwardVector() * 120.;

			CanMantle = true;

			FVector SecondSphereLocation = MantlePos2 + FVector(0., 0., 20.);

			TArray<AActor*> IgnoreSecondSphereActors;
			FHitResult SecondSphereHitResult;

			const bool SecondSphereHit =
				UKismetSystemLibrary::SphereTraceSingle(Owner, SecondSphereLocation, SecondSphereLocation, 10.,
					ETraceTypeQuery::TraceTypeQuery1, false, IgnoreSecondSphereActors, EDrawDebugTrace::None, SecondSphereHitResult, true);
			if (SecondSphereHit)
			{
				CanMantle = false;
			}
			else
			{
				MantlePos2 = FirstSphereHitResult.ImpactPoint + Owner->GetActorForwardVector() * 50.;
			}

			if (MantlePos1 == FVector::ZeroVector || MantlePos2 == FVector::ZeroVector)
			{
				CanMantle = false;
				return FMantlePosStruct(MantlePos1, MantlePos2);
			}
			else
			{
				FVector ThirdSphereEnd = MantlePos2 + FVector(0., 0., 100.);
				FVector ThirdSphereStart = FVector(MantlePos1.X, MantlePos1.Y, ThirdSphereEnd.Z);

				TArray<AActor*> IgnoreThridSphereActors;
				FHitResult ThirdSphereHitResult;

				const bool ThirdSphereHit =
					UKismetSystemLibrary::SphereTraceSingle(Owner, ThirdSphereStart, ThirdSphereEnd, 20.,
						ETraceTypeQuery::TraceTypeQuery1, false, IgnoreThridSphereActors, EDrawDebugTrace::None, ThirdSphereHitResult, true);

				if (ThirdSphereHit)
				{
					CanMantle = false;
					return FMantlePosStruct(MantlePos1, MantlePos2);
				}
				else
				{
					return FMantlePosStruct(MantlePos1, MantlePos2);
				}
			}
		}
		else
		{
			CanMantle = false; 
			return FMantlePosStruct(); 
		}
	}
	else
	{
		CanMantle = false; 
		return FMantlePosStruct();
	}
}

void UMantlingComponent::PlayMantle(FVector Location1, FVector Location2, float ZOffsetHand, float ZOffsetLanding, float MontageLength)
{
	Owner->SetActorEnableCollision(false); 

	CharMoveComp->SetMovementMode(EMovementMode::MOVE_Flying); 


	FMotionWarpingTarget MantleTarget1 = {}; 
	MantleTarget1.Name = FName("MantlePoint1"); 
	MantleTarget1.Location = Location1 + FVector(0., 0., ZOffsetHand); 
	MantleTarget1.Rotation = Owner->GetActorRotation(); 

	FMotionWarpingTarget MantleTarget2 = {}; 
	MantleTarget2.Name = FName("MantlePoint2"); 
	MantleTarget2.Location = Location2 + FVector(0., 0., ZOffsetLanding); 
	MantleTarget2.Rotation = Owner->GetActorRotation(); 

	MotionWarping->AddOrUpdateWarpTarget(MantleTarget1); 
	MotionWarping->AddOrUpdateWarpTarget(MantleTarget2); 

	CharMesh->GetAnimInstance()->Montage_Play(MantlingMontage);

	FTimerHandle TimerHandle; 
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Delay Executed by Playing Mantling Montage"))
		}, MontageLength, false);

	Owner->SetActorEnableCollision(true); 

	CharMoveComp->SetMovementMode(EMovementMode::MOVE_Falling);
}
