// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/Controller/ParkourPlayerController.h"
#include "Data/Input/ParkourPlayerInputDataConfig.h"



void AParkourPlayerController::BeginPlay()
{
	Super::BeginPlay(); 

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	const UParkourPlayerInputDataConfig* ParkourPlayerInputDataConfig = GetDefault<UParkourPlayerInputDataConfig>();
	Subsystem->AddMappingContext(ParkourPlayerInputDataConfig->InputMappingContext, 0);

}

void AParkourPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn); 

	AParkourPlayer* ParkourPlayer = Cast<AParkourPlayer>(aPawn); 
}


void AParkourPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	const UParkourPlayerInputDataConfig* ParkourPlayerInputDataConfig = GetDefault<UParkourPlayerInputDataConfig>();
	
	
	// Default
	EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Look, ETriggerEvent::Triggered, this, &ThisClass::Look);

	// Jump 
	EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Jump, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Jump, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
	
	// Sprint
	EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Sprint, ETriggerEvent::Triggered, this, &ThisClass::SprintTriggered);
	EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Sprint, ETriggerEvent::Started, this, &ThisClass::SprintStarted);
	EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Sprint, ETriggerEvent::Completed, this, &ThisClass::SprintCompleted);

	// Grapple Rope
	EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->GrappleRope, ETriggerEvent::Triggered, this, &ThisClass::GrappleHook);

	// Slide
	EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Sprint, ETriggerEvent::Triggered, this, &ThisClass::Slide);

	// Mantle 
	EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Mantle, ETriggerEvent::Triggered, this, &ThisClass::Mantle);
		
	// Ledge Climb

	// Attack 
	}

void AParkourPlayerController::Move(const FInputActionValue& Value)
{
	AParkourPlayer* ParkourPlayer = Cast<AParkourPlayer>(GetPawn());
	ensure(ParkourPlayer);

	ParkourPlayer->Move(Value); 
}
void AParkourPlayerController::Look(const FInputActionValue& Value)
{
	AParkourPlayer* ParkourPlayer = Cast<AParkourPlayer>(GetPawn());
	ensure(ParkourPlayer);

	ParkourPlayer->Look(Value);
}
void AParkourPlayerController::Jump(const FInputActionValue& Value)
{
	AParkourPlayer* ParkourPlayer = Cast<AParkourPlayer>(GetPawn());
	ensure(ParkourPlayer);

	ParkourPlayer->Jump(Value);
}
void AParkourPlayerController::StopJumping(const FInputActionValue& Value)
{
	AParkourPlayer* ParkourPlayer = Cast<AParkourPlayer>(GetPawn());
	ensure(ParkourPlayer);

	ParkourPlayer->StopJumping(Value);
}
void AParkourPlayerController::SprintTriggered(const FInputActionValue& Value)
{
	AParkourPlayer* ParkourPlayer = Cast<AParkourPlayer>(GetPawn());
	ensure(ParkourPlayer);

	ParkourPlayer->SprintingComponent->SprintTriggered(Value); 
}
void AParkourPlayerController::SprintStarted(const FInputActionValue& Value)
{
	AParkourPlayer* ParkourPlayer = Cast<AParkourPlayer>(GetPawn());
	ensure(ParkourPlayer);

	ParkourPlayer->SprintingComponent->SprintStarted(Value);
}
void AParkourPlayerController::SprintCompleted(const FInputActionValue& Value)
{
	AParkourPlayer* ParkourPlayer = Cast<AParkourPlayer>(GetPawn());
	ensure(ParkourPlayer);

	ParkourPlayer->SprintingComponent->SprintCompleted(Value);
}
void AParkourPlayerController::GrappleHook(const FInputActionValue& Value)
{
	AParkourPlayer* ParkourPlayer = Cast<AParkourPlayer>(GetPawn());
	ensure(ParkourPlayer);

	ParkourPlayer->GrapplingRopeComponent->GrappleHook(Value);
}
void AParkourPlayerController::Slide(const FInputActionValue& Value)
{
	AParkourPlayer* ParkourPlayer = Cast<AParkourPlayer>(GetPawn());
	ensure(ParkourPlayer);

	ParkourPlayer->SlidingComponent->Slide(Value);
}
void AParkourPlayerController::Mantle(const FInputActionValue& Value)
{
	AParkourPlayer* ParkourPlayer = Cast<AParkourPlayer>(GetPawn());
	ensure(ParkourPlayer);

	ParkourPlayer->MantlingComponent->Mantle(Value);
}


