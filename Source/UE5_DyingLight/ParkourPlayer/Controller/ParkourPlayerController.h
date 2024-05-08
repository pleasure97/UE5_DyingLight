// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
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
	virtual void SetupInputComponent() override; 

protected:
	void Move(const FInputActionValue& InputActionValue); 
	void GrappleRope(const FInputActionValue& InputActionValue);
	void Slide(const FInputActionValue& InputActionValue); 
	void Mantle(const FInputActionValue& InputActionValue); 
	void LedgeClimb(const FInputActionValue& InputActionValue); 
};
