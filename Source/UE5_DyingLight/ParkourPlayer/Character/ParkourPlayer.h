// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "MotionWarpingComponent.h"
#include "UE5_DyingLightCharacter.h"
#include "ParkourPlayer.generated.h"


UCLASS()
class UE5_DYINGLIGHT_API AParkourPlayer : public AUE5_DyingLightCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AParkourPlayer(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSource; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMotionWarpingComponent* MotionWarping;


// General
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanMove = true; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsGrappling = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSliding = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMantling = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsLedgeClimbing = true;



// Sliding

// Sprinting

// Mantling

// LedgeClimbing 



};
