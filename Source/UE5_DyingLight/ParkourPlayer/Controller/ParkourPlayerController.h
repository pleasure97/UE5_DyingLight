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
	virtual void SetupInputComponent() override; 
};
