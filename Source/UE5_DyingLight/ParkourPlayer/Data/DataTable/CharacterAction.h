// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimMontage.h"
#include "Animation/BlendSpace.h"
#include "CharacterAction.generated.h"


/**
 * 
 */
USTRUCT()
struct UE5_DYINGLIGHT_API FCharacterAction : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> MontageRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UBlendSpace*> BlendSpaceRef;
};
