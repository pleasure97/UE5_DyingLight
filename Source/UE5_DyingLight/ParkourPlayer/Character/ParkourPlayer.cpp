// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/Character/ParkourPlayer.h"

// Sets default values
AParkourPlayer::AParkourPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Initialize a skeletal mesh compoennt and related anim blueprint 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if (SkeletalMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMeshAsset.Object); 
	}
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, 0.f, -90.f)); 

	// Create a Motion Warping Component
	MotionWarping = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));

	// Create an AI Perception Stimuli Source Component
	AIPerceptionStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSource"));

	// Create a Grapple Rope Component
	GrappleRope = CreateDefaultSubobject<UCableComponent>(TEXT("GrappleRope"));
	GrappleRope->SetRelativeLocation(FVector(0.f, 0.f, 40.f));
	GrappleRope->EndLocation = FVector(0.f, 0.f, 40.f);
	GrappleRope->CableLength = 0.f;
	GrappleRope->CableWidth = 8.f;

	// Create a Sprinting Component
	SprintingComponent = CreateDefaultSubobject<USprintingComponent>(TEXT("SprintingComponent"));

	// Create a Sliding Component
	SlidingComponent = CreateDefaultSubobject<USlidingComponent>(TEXT("SlidingComponent")); 

	// Create a Mantling Component 
	MantlingComponent = CreateDefaultSubobject<UMantlingComponent>(TEXT("MantlingComponent"));
}
	

// Called when the game starts or when spawned
void AParkourPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AParkourPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AParkourPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); 
}

void AParkourPlayer::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AParkourPlayer::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AParkourPlayer::Jump(const FInputActionValue& Value)
{
	ACharacter::Jump(); 
}

void AParkourPlayer::StopJumping(const FInputActionValue& Value)
{
	ACharacter::StopJumping(); 
}

