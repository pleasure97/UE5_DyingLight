// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "BasicInputDataConfig.generated.h"

/**
 * 
 */
UCLASS()
class UE5_DYINGLIGHT_API UBasicInputDataConfig : public UObject
{
	GENERATED_BODY()

public:
	UBasicInputDataConfig();
	UInputMappingContext* InputMappingContext = nullptr;
	
public:
	UInputAction* Move = nullptr;
	UInputAction* Look = nullptr;
	UInputAction* Jump = nullptr;
	UInputAction* GrappleRope = nullptr;
	UInputAction* Slide = nullptr;
	UInputAction* Mantle = nullptr;
	UInputAction* Sprint = nullptr;
	UInputAction* DropKick = nullptr;
	UInputAction* Attack = nullptr;

};
