// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/Component/SlidingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
USlidingComponent::USlidingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

	// To be implemented
	// Curve, Timeline, Montage may need to be loaded 
	
}


// Called every frame
void USlidingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USlidingComponent::Slide()
{
	AActor* Owner = GetOwner(); 
	ensure(Owner); 

	UCharacterMovementComponent* CharMoveComp = Cast<UCharacterMovementComponent>(Owner->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	
	if (CharMoveComp->Velocity.Size() > 200.f)
	{
		USkeletalMeshComponent* CharMesh = Cast<USkeletalMeshComponent>(Owner->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

		if (CharMesh->GetAnimInstance()->IsAnyMontagePlaying() && CharMoveComp->IsFalling())
		{
			return;
		}

		IsSliding = true; 

		CharMesh->GetAnimInstance()->Montage_Play(SlidingMontage); 

		RevertCapsule(); 


	}

	

}

void USlidingComponent::RevertCapsule()
{
	AActor* Owner = GetOwner(); 
	ensure(Owner); 

	UCharacterMovementComponent* CharMoveComp = Cast<UCharacterMovementComponent>(Owner->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	
	if (!CharMoveComp->IsCrouching())
	{

	}

	UCapsuleComponent* CapsComp = Cast<UCapsuleComponent>(Owner->GetComponentByClass(UCapsuleComponent::StaticClass())); 

	// float HalfHeight = 
	// CapsComp->SetCapsuleHalfHeight(HalfHeight, true);

	USkeletalMeshComponent* CharMesh = Cast<USkeletalMeshComponent>(Owner->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	CharMesh->SetRelativeLocation(); 






}


