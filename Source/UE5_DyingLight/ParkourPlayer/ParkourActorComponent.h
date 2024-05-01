// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CPP_Parkouror.h"



#include "ParkourActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DYINGLIGHT_API UParkourActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UParkourActorComponent();

	enum EDrawDebugTrace::Type Setting = EDrawDebugTrace::ForDuration;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	void ClimbTrace(ACharacter* CharacterRef, FVector& Start, FVector& Middle, FVector& Last, bool& Sussess,float Radius);
	void ClimbOn(ACharacter* CharacterRef, FVector ActionValue, bool& CanHanging, float& HangingValue);
	void ClimbUp(ACPP_Parkouror* CharacterRef, bool& CanMove);
};
