// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CableComponent.h"
#include "MotionWarpingComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Component/GrapplingRopeComponent.h"
#include "Component/SlidingComponent.h"
#include "Component/SprintingComponent.h"
#include "Component/MantlingComponent.h"
#include "InputActionValue.h"
#include "ParkourPlayer.generated.h"


UCLASS()
class UE5_DYINGLIGHT_API AParkourPlayer : public ACharacter
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
	UPROPERTY(EditAnywhere)
	UCableComponent* GrappleRope;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMotionWarpingComponent* MotionWarping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSource; 

// parkour action component
protected:

	UPROPERTY(EditAnywhere)
	UGrapplingRopeComponent* GrapplingRopeComponent = nullptr;

	UPROPERTY(EditAnywhere)
	USlidingComponent* SlidingComponent = nullptr;

	UPROPERTY(EditAnywhere)
	USprintingComponent* SprintingComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UMantlingComponent* MantlingComponent = nullptr; 


// parkour action state 
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


public:
	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	virtual void Jump(const FInputActionValue& Value);
	virtual void StopJumping(const FInputActionValue& nValue);



};
