// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
#include "InputActionValue.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SlidingComponent.generated.h"


USTRUCT()
struct FAngleDirectionStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	double Angle; 

	UPROPERTY(EditAnywhere)
	bool IsSlopeUp; 
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DYINGLIGHT_API USlidingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlidingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// For caching owner's another component
protected:
	UPROPERTY()
	AActor* Owner = nullptr;

	UPROPERTY()
	UCharacterMovementComponent* CharMoveComp = nullptr;

	UPROPERTY()
	USkeletalMeshComponent* CharMesh = nullptr;

	UPROPERTY()
	UCapsuleComponent* CapsuleComp = nullptr; 


protected:
	UPROPERTY(EditAnywhere, Category = "Sliding")
	bool IsSliding = false; 

	UPROPERTY(EditAnywhere, Category = "Sliding")
	FVector CurrentSlidingVelocity; 

	UPROPERTY(EditAnywhere, Category = "Sliding")
	double CurrentAngle; 

	UPROPERTY(EditAnywhere, Category = "Sliding")
	double SpeedToStopSliding = 50.f;

	UPROPERTY(EditAnywhere, Category = "Sliding")
	FRotator DefaultYawRotation; 

	UPROPERTY(EditAnywhere, Category = "Sliding")
	bool IsTraceCeiling = false; 

protected:
	UPROPERTY(EditAnywhere, Category = "Sliding|Capsule")
	UTimelineComponent* ScaleCapsuleTimeline = nullptr;

	UPROPERTY(EditAnywhere, Category = "Sliding|Rotation")
	UTimelineComponent* ResetSlideRotation = nullptr;

protected:
	UPROPERTY(EditAnywhere, Category = "Sliding|Montage")
	UAnimMontage* SlidingMontage; 

	UPROPERTY(EditAnywhere, Category = "Sliding|Montage")
	UAnimMontage* SlidingEndMontage;

public:
	UFUNCTION()
	void Slide(const FInputActionValue& Value);

	UFUNCTION()
	void RevertCapsule();
	
	UFUNCTION()
	void ScaleCapsule(float Value); 

	UFUNCTION()
	void CheckIfOnFloor(float TraceRadius, float TraceHalfHeight, float MontageBlendOutTime); 

	UFUNCTION()
	void CheckShouldContinueSliding(FTimerHandle SlidingTraceHandle); 

	UFUNCTION()
	void ContinueSliding(FTimerHandle SildingTraceHandle, FTimerHandle ContinueSlidingHandle); 

	UFUNCTION()
	FAngleDirectionStruct FindCurrentFloorAngleAndDirection(); 

	UFUNCTION()
	void PlayGetUpAnimation(FTimerHandle SlideTraceHandle); 

	UFUNCTION()
	void ResetXYRotation(float Value); 

	UFUNCTION()
	void ResetWalkMaxSpeedAndAccel(); 

	UFUNCTION()
	bool CheckIfHitSurface(float TraceZOffset, float Radius, float CompareAngle, EDrawDebugTrace::Type DrawDebugType);
};
