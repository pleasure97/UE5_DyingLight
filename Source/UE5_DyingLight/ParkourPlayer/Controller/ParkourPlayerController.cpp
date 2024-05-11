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

	SetControlRotation(FRotator(-30., 0., 0.));
}

void AParkourPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	const UParkourPlayerInputDataConfig* ParkourPlayerInputDataConfig = GetDefault<UParkourPlayerInputDataConfig>();
	
	AParkourPlayer* ParkourPlayer = Cast<AParkourPlayer>(GetPawn());

	if (ParkourPlayer)
	{
		// Default
		EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Move, ETriggerEvent::Triggered, ParkourPlayer, &AParkourPlayer::Move);
		EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Look, ETriggerEvent::Triggered, ParkourPlayer, &AParkourPlayer::Look);

		// Jump 
		EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Jump, ETriggerEvent::Started, ParkourPlayer, &AParkourPlayer::Jump);
		EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Jump, ETriggerEvent::Completed, ParkourPlayer, &AParkourPlayer::StopJumping);
	
		// Sprint
		EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Sprint, ETriggerEvent::Triggered, ParkourPlayer->SprintingComponent, &USprintingComponent::SprintTriggered);
		EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Sprint, ETriggerEvent::Started, ParkourPlayer->SprintingComponent, &USprintingComponent::SprintStarted);
		EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Sprint, ETriggerEvent::Completed, ParkourPlayer->SprintingComponent, &USprintingComponent::SprintCompleted);

		// Grapple Rope
		EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->GrappleRope, ETriggerEvent::Triggered, ParkourPlayer->GrapplingRopeComponent, &UGrapplingRopeComponent::GrappleHook);

		// Slide
		EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Sprint, ETriggerEvent::Triggered, ParkourPlayer->SlidingComponent, &USlidingComponent::Slide);

		// Mantle 
		EnhancedInputComponent->BindAction(ParkourPlayerInputDataConfig->Mantle, ETriggerEvent::Triggered, ParkourPlayer->MantlingComponent,&UMantlingComponent::Mantle);
		
		// Ledge Climb

		// Attack 
	}
}

