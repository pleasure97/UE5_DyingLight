// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_DyingLightGameMode.h"
#include "UE5_DyingLightCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE5_DyingLightGameMode::AUE5_DyingLightGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
