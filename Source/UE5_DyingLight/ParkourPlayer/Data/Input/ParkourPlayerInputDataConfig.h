// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParkourPlayer/Data/Input/BasicInputDataConfig.h"
#include "ParkourPlayerInputDataConfig.generated.h"

/**
 * 
 */
UCLASS()
class UE5_DYINGLIGHT_API UParkourPlayerInputDataConfig : public UObject
{
	GENERATED_BODY()
	
public:
	UParkourPlayerInputDataConfig();
	UInputMappingContext* InputMappingContext = nullptr;

public:
	// default 
	UInputAction* Move = nullptr;
	UInputAction* Look = nullptr;
	UInputAction* Jump = nullptr;

	// parkour action 
	UInputAction* Sprint = nullptr;
	UInputAction* GrappleRope = nullptr;
	UInputAction* Slide = nullptr;
	UInputAction* Mantle = nullptr;

	// attack 
	UInputAction* DropKick = nullptr;
	UInputAction* Attack = nullptr;
};
