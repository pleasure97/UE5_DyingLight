// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/Character/ParkourPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AParkourPlayer::AParkourPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GrappleRope = CreateDefaultSubobject<UCableComponent>(TEXT("GrappleRope")); 
	GrappleRope->SetupAttachment(GetCapsuleComponent()); 
	GrappleRope->SetRelativeLocation(FVector(0.f, 0.f, 40.f)); 
	GrappleRope->EndLocation = FVector(0.f, 0.f, 40.f); 
	GrappleRope->CableLength = 0.f; 
	GrappleRope->CableWidth = 8.f; 
	// GrappleRope->SetVisibility

	AIPerceptionStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSource"));
	MotionWarping = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping")); 
}



//void ATestCharacter::BeginPlay()
//{
//	// Call the base class  
//	Super::BeginPlay();
//
//	//Add Input Mapping Context
//	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
//	{
//		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
//		{
//			Subsystem->AddMappingContext(DefaultMappingContext, 0);
//		}
//	}
//}
//
////////////////////////////////////////////////////////////////////////////
//// Input
//
//void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	// Set up action bindings
//	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
//
//		// Jumping
//		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
//		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
//
//		// Moving
//		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATestCharacter::Move);
//
//		// Looking
//		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATestCharacter::Look);
//	}
//	else
//	{
//		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
//	}
//}
//
//void ATestCharacter::Move(const FInputActionValue& Value)
//{
//	// input is a Vector2D
//	FVector2D MovementVector = Value.Get<FVector2D>();
//
//	if (Controller != nullptr)
//	{
//		// find out which way is forward
//		const FRotator Rotation = Controller->GetControlRotation();
//		const FRotator YawRotation(0, Rotation.Yaw, 0);
//
//		// get forward vector
//		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
//
//		// get right vector 
//		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
//
//		// add movement 
//		AddMovementInput(ForwardDirection, MovementVector.Y);
//		AddMovementInput(RightDirection, MovementVector.X);
//	}
//}
//
//void ATestCharacter::Look(const FInputActionValue& Value)
//{
//	// input is a Vector2D
//	FVector2D LookAxisVector = Value.Get<FVector2D>();
//
//	if (Controller != nullptr)
//	{
//		// add yaw and pitch input to controller
//		AddControllerYawInput(LookAxisVector.X);
//		AddControllerPitchInput(LookAxisVector.Y);
//	}
//}
//
//







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

