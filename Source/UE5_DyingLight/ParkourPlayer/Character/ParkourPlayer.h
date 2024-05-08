// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CableComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "MotionWarpingComponent.h"
#include "UE5_DyingLightCharacter.h"
#include "Components/TimelineComponent.h"
#include "ParkourPlayer.generated.h"


UCLASS()
class UE5_DYINGLIGHT_API AParkourPlayer : public AUE5_DyingLightCharacter
{
	GENERATED_BODY()

	friend class AParkourPlayerController;

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
	UCableComponent* GrappleRope; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSource; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMotionWarpingComponent* MotionWarping;


// General
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanMove = true; 

// Grappling Rope
protected:
	UPROPERTY(EditAnywhere)
	bool CanGrappleHook = true; 

	UPROPERTY(EditAnywhere)
	float GrappleHookDistance = 1500.f;

	UPROPERTY(EditAnywhere)
	FVector HookLocation; 

	UPROPERTY(EditAnywhere)
	float GrappleHookCoolDown = 1.f;

	UPROPERTY(EditAnywhere)
	bool GrappleHookEnabled = true; 

	float ShootGrappleHook(); 

	UPROPERTY(EditAnywhere)
	UTimelineComponent* GrappleShootTimeline = nullptr; 


// Sliding

// Sprinting

// Mantling

// LedgeClimbing 



};
