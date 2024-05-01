// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "CPP_ParkourPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE5_DYINGLIGHT_API ACPP_ParkourPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanMove = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanHanging = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HangingValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool RunOnOff = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DoubleTab{ 0 };

	bool bFirstTapOccurred = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanDoubleTab = false;

	UDataTable* AnimationDataTable = nullptr;

	float CurrentWalkSpeed;

	FTimerHandle TimerHandle;

	FVector StartPos; 
	FVector MiddlePos;
	FVector LastPos;

	UPROPERTY(EditAnywhere)
	class UParkourActorComponent* ParkourActorComponent;



public:
	ACPP_ParkourPlayerController();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;


protected:
	void StartDelay(float DelayDuration);
	void OnDelayComplete();

protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void OnMoveDoubleTab(const FInputActionValue& InputActionValue);
	void OnMoveCompleted(const FInputActionValue& InputActionValue);
	void OnLook(const FInputActionValue& InputActionValue);
	void OnJump(const FInputActionValue& InputActionValue);
	void OffJump(const FInputActionValue& InputActionValue);
	void LeftShift(const FInputActionValue& InputActionValue);
	void LeftShiftCompleted(const FInputActionValue& InputActionValue);
	void LeftClick(const FInputActionValue& InputActionValue);

	
};
