// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CableComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "MotionWarpingComponent.h"
#include "ParkourPlayer.generated.h"


UCLASS()
class UE5_DYINGLIGHT_API AParkourPlayer : public ACharacter
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
	USpringArmComponent* CameraBoom; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* FollowCamera; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCableComponent* GrappleRope; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSource; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMotionWarpingComponent* MotionWarping;


// Grappling Rope


// Sliding

// Sprinting

// Mantling

// LedgeClimbing 



};
