// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/Controller/DefaultPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Data/Input/BasicInputDataConfig.h"



void ADefaultPlayerController::BeginPlay()
{
}

void ADefaultPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	const UBasicInputDataConfig* BasicInputDataConfig = GetDefault<UBasicInputDataConfig>();
	EnhancedInputComponent->BindAction(BasicInputDataConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(BasicInputDataConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
}
