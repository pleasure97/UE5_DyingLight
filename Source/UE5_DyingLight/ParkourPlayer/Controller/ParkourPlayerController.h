// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "ParkourPlayer/Character/ParkourPlayer.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ParkourPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE5_DYINGLIGHT_API AParkourPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override; 
	virtual void OnPossess(APawn* aPawn) override;
	virtual void SetupInputComponent() override; 

protected:
	// Default
	virtual void Move(const FInputActionValue& Value); 
	virtual void Look(const FInputActionValue& Value);

	// Jump 
	virtual void Jump(const FInputActionValue& Value);
	virtual void StopJumping(const FInputActionValue& Value);

	// Sprint
	virtual void SprintTriggered(const FInputActionValue& Value);
	virtual void SprintStarted(const FInputActionValue& Value);
	virtual void SprintCompleted(const FInputActionValue& Value);

	// Grapple Rope
	virtual void GrappleHook(const FInputActionValue& Value);

	// Slide
	virtual void Slide(const FInputActionValue& Value);

	// Mantle 
	virtual void Mantle(const FInputActionValue& Value);
	
};
