// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/CPP_ParkourPlayerController.h"
#include "GameFramework//Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CPP_Parkouror.h"
#include "GameFramework//CharacterMovementComponent.h"
#include "ParkourActorComponent.h"
#include "Data/Input/BasicInputDataConfig.h"
#include "TimerManager.h"
#include "Data/DataTable/CharacterAction.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"

ACPP_ParkourPlayerController::ACPP_ParkourPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	ParkourActorComponent = CreateDefaultSubobject<UParkourActorComponent>("Parkour");
	
}

void ACPP_ParkourPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ACPP_ParkourPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	const UBasicInputDataConfig* BasicInputDataConfig = GetDefault<UBasicInputDataConfig>();
	Subsystem->AddMappingContext(BasicInputDataConfig->InputMappingContext, 0);

	SetControlRotation(FRotator(-30, 0, 0));
}

void ACPP_ParkourPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	const UBasicInputDataConfig* BasicInputDataConfig = GetDefault<UBasicInputDataConfig>();
	EnhancedInputComponent->BindAction(BasicInputDataConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	EnhancedInputComponent->BindAction(BasicInputDataConfig->Move, ETriggerEvent::Started, this, &ThisClass::OnMoveDoubleTab);
	EnhancedInputComponent->BindAction(BasicInputDataConfig->Move, ETriggerEvent::Completed, this, &ThisClass::OnMoveCompleted);
	EnhancedInputComponent->BindAction(BasicInputDataConfig->Look, ETriggerEvent::Triggered, this, &ThisClass::OnLook);
	EnhancedInputComponent->BindAction(BasicInputDataConfig->Jump, ETriggerEvent::Started, this, &ThisClass::OnJump);
	EnhancedInputComponent->BindAction(BasicInputDataConfig->Jump, ETriggerEvent::Completed, this, &ThisClass::OffJump);
	EnhancedInputComponent->BindAction(BasicInputDataConfig->LeftShift, ETriggerEvent::Triggered, this, &ThisClass::LeftShift);
	EnhancedInputComponent->BindAction(BasicInputDataConfig->LeftShift, ETriggerEvent::Completed, this, &ThisClass::LeftShiftCompleted);
	EnhancedInputComponent->BindAction(BasicInputDataConfig->LeftClick, ETriggerEvent::Started, this, &ThisClass::LeftClick);
}

void ACPP_ParkourPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ACPP_Parkouror* ControlledPawn = Cast<ACPP_Parkouror>(GetPawn());
	const FVector ActorLocation = ControlledPawn->GetActorLocation();
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Blue, FString::SanitizeFloat(ControlledPawn->GetCharacterMovement()->MaxWalkSpeed));
	if (!RunOnOff)
	{
		float MaxWalkSpeed = ControlledPawn->GetCharacterMovement()->GetMaxSpeed();
		CurrentWalkSpeed = FMath::Clamp(MaxWalkSpeed - (MaxWalkSpeed / 2 * GetWorld()->GetDeltaSeconds()), 300, 900);
		ControlledPawn->GetCharacterMovement()->MaxWalkSpeed = CurrentWalkSpeed;
	}
	
	if (ControlledPawn->GetCharacterMovement()->IsFalling())
	{
		if (CanMove && !bCanHanging) 
		{
			ParkourActorComponent->ClimbTrace(ControlledPawn,StartPos, MiddlePos, LastPos, bCanHanging, ControlledPawn->GetCapsuleComponent()->GetScaledCapsuleRadius());
		}
	}
}

void ACPP_ParkourPlayerController::StartDelay(float DelayDuration)
{
}

void ACPP_ParkourPlayerController::OnDelayComplete()
{
	DoubleTab = 0;
	CanDoubleTab = false;
}

void ACPP_ParkourPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	APawn* ControlledPawn = GetPawn();
	ACPP_Parkouror* CharacterRef = Cast<ACPP_Parkouror>(GetPawn());
	const FRotator Rotation = K2_GetActorRotation();
	const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0.);
	const FVector ForwardVector = YawRotation.Vector();
	const FVector RightVector = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);
	UCharacterMovementComponent* MovementComponent = CharacterRef->GetCharacterMovement();
	const FVector ActionValue = InputActionValue.Get<FVector>();
	// Hanging 실행 구문
	ParkourActorComponent->ClimbOn(CharacterRef, ActionValue, bCanHanging, HangingValue);
	if (CanMove && !bCanHanging) ControlledPawn->AddMovementInput(ForwardVector, ActionValue.Y);
	if (CanMove && !bCanHanging) if (CharacterRef->GetCharacterMovement()->MaxWalkSpeed < 500)ControlledPawn->AddMovementInput(RightVector, ActionValue.X);
	if (abs(ActionValue.X) > 0) CharacterRef->SideMove = ActionValue.X * 100;

}

void ACPP_ParkourPlayerController::OnMoveDoubleTab(const FInputActionValue& InputActionValue)
{
	ACPP_Parkouror* CharacterRef = Cast<ACPP_Parkouror>(GetPawn());
	const FRotator Rotation = K2_GetActorRotation();
	const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0.);
	const FVector ForwardVector = YawRotation.Vector();
	const FVector RightVector = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);
	//GEngine->AddOnScreenDebugMessage(5, 5.0f, FColor::Blue, "DoubleTap");
	if (DoubleTab == 0)
	{
		++DoubleTab;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACPP_ParkourPlayerController::OnDelayComplete, 0.2f, false);
	}
	else
	{
		// 두 번째 탭이 시간 내에 발생하면 Double Tap으로 처리

		if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
		{
			// 타이머 취소
			GEngine->AddOnScreenDebugMessage(5, 0.9f, FColor::Blue, "DoubleTap");
			DoubleTab = 0;
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			CanDoubleTab = true;
			const FVector ActionValue = InputActionValue.Get<FVector>();

			if (CanMove && abs(ActionValue.Y)) CharacterRef->LaunchCharacter((ForwardVector * (ActionValue.Y * 1800)) + FVector(0, 0, -20), true, true);
			if (CanMove && abs(ActionValue.X)) CharacterRef->LaunchCharacter((RightVector * (ActionValue.X * 1800)) + FVector(0, 0, -20), true, true);

		}
	}
}

void ACPP_ParkourPlayerController::OnMoveCompleted(const FInputActionValue& InputActionValue)
{
	ACPP_Parkouror* CharacterRef = Cast<ACPP_Parkouror>(GetPawn());
	CharacterRef->SideMove = 0;
	HangingValue = 0;
}

void ACPP_ParkourPlayerController::OnLook(const FInputActionValue& InputActionValue)
{
	const FVector ActionValue = InputActionValue.Get<FVector>();
	if (!RunOnOff)
	{
		if (CanMove && !bCanHanging)AddYawInput(ActionValue.X);
		if (CanMove && !bCanHanging)AddPitchInput(ActionValue.Y);
	}
	else
	{
		if (CanMove)AddYawInput(ActionValue.X / CurrentWalkSpeed * 30);
		if (CanMove)AddPitchInput(ActionValue.Y / CurrentWalkSpeed * 30);
	}
}

void ACPP_ParkourPlayerController::OnJump(const FInputActionValue& InputActionValue)
{
	ACharacter* ControlledPawn = Cast<ACharacter>(GetPawn());
	const FVector ActorLocation = ControlledPawn->GetActorLocation();


	if (CanMove) ControlledPawn->Jump();
}

void ACPP_ParkourPlayerController::OffJump(const FInputActionValue& InputActionValue)
{
	ACharacter* ControlledPawn = Cast<ACharacter>(GetPawn());

	if (CanMove) ControlledPawn->StopJumping();
}

void ACPP_ParkourPlayerController::LeftShift(const FInputActionValue& InputActionValue)
{
	RunOnOff = true;
	ACharacter* CharacterRef = Cast<ACharacter>(GetPawn());
	float MaxWalkSpeed = CharacterRef->GetCharacterMovement()->GetMaxSpeed();
	CurrentWalkSpeed = FMath::Clamp(MaxWalkSpeed + (MaxWalkSpeed / 2 * GetWorld()->GetDeltaSeconds()), 300, 900);
	CharacterRef->GetCharacterMovement()->MaxWalkSpeed = CurrentWalkSpeed;
}

void ACPP_ParkourPlayerController::LeftShiftCompleted(const FInputActionValue& InputActionValue)
{
	RunOnOff = false;
}

void ACPP_ParkourPlayerController::LeftClick(const FInputActionValue& InputActionValue)
{

}
