// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/Component/SprintingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
USprintingComponent::USprintingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SprintingFOV = CreateDefaultSubobject<UTimelineComponent>(TEXT("SprintingFOV")); 
	{
		static ConstructorHelpers::FObjectFinder<UCurveFloat> ObjectFinder(TEXT("/Script/Engine.CurveFloat'/Game/Blueprints/Curves/Curve_SprintingFOV.Curve_SprintingFOV'"));
		ensure(ObjectFinder.Object); 

		FOnTimelineFloat Delegate; 
		Delegate.BindUFunction(this, TEXT("UpdateFOV")); 
		
		SprintingFOV->AddInterpFloat(ObjectFinder.Object, Delegate); 
	}

	SprintingStopMontage = CreateDefaultSubobject<UAnimMontage>(TEXT("SprintingStopMontage")); 
	{
		static ConstructorHelpers::FObjectFinder<UAnimMontage> ObjectFinder(TEXT("/Script/Engine.AnimMontage'/Game/Parkour/Sprinting/Animations/RunToStop_UE_Montage.RunToStop_UE_Montage'"));
		ensure(ObjectFinder.Object);
	}
}


// Called when the game starts
void USprintingComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner(); 
	ensure(Owner); 

	CharMoveComp = Cast<UCharacterMovementComponent>(Owner->GetComponentByClass(UCharacterMovementComponent::StaticClass())); 
	ensure(CharMoveComp); 

	FollowCamera = Cast<UCameraComponent>(Owner->GetComponentByClass(UCameraComponent::StaticClass())); 
	ensure(FollowCamera); 

	CharMesh = Cast<USkeletalMeshComponent>(Owner->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	ensure(CharMesh); 
}


// Called every frame
void USprintingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USprintingComponent::SprintTriggered()
{
	

	if (CharMoveComp->Velocity.Size2D() > 10.f && (CharMoveComp->GetCurrentAcceleration() != FVector::ZeroVector))
	{

	}
	else
	{

	}
}

void USprintingComponent::SprintStarted()
{
	IsSprinting = true; 

	CharMoveComp->MaxWalkSpeed = SprintSpeed; 

	SprintingFOV->Play(); 

}

void USprintingComponent::SprintCompleted()
{
	CharMoveComp->MaxWalkSpeed = DefaultWalkSpeed; 

	SprintingFOV->Reverse(); 

	// To be implemented
	if (TriggeredSeconds > 0.75)
	{
		if (!CharMoveComp->IsFalling())
		{
			if (IsSprinting)
			{
				if (CharMoveComp->GetLastUpdateVelocity().Size() >= 50.)
				{
					IsSprinting = false; 
					CharMesh->GetAnimInstance()->Montage_Play(SprintingStopMontage); 
				}
			}
		}
	}
	else
	{
		IsSprinting = false; 
	}

}

void USprintingComponent::UpdateFOV(float Value)
{
	double InFOV = UKismetMathLibrary::Lerp(90., 100., Value);
	FollowCamera->SetFieldOfView(InFOV); 
}

