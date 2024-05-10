// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "SlidingComponent.generated.h"


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

protected:
	UPROPERTY(EditAnywhere, Category = "Sliding")
	bool IsSliding = false; 

	UPROPERTY(EditAnywhere, Category = "Sliding")
	FVector CurrentSlidingVelocity; 

	UPROPERTY(EditAnywhere, Category = "Sliding")
	float CurrentAngle; 

	UPROPERTY(EditAnywhere, Category = "Sliding")
	FRotator DefaultYawRotation; 

	UPROPERTY(EditAnywhere, Category = "Sliding")
	bool IsTraceCeiling = false; 

protected:
	UPROPERTY(EditAnywhere, Category = "Sliding|Capsule")
	UTimelineComponent* ScaleCapsuleTimeline = nullptr;

	// curve reference address
	// TEXT("/Script/Engine.CurveFloat'/Game/Blueprints/Curves/Curve_CapsuleScale.Curve_CapsuleScale'")
	UPROPERTY(EditAnywhere, Category = "Sliding|Capsule")
	UCurveFloat* CapsuleScale = nullptr;

protected:
	UPROPERTY(EditAnywhere, Category = "Sliding|Rotation")
	UTimelineComponent* ResetSlideRotation = nullptr;

	// curve reference address
	// TEXT("/Script/Engine.CurveFloat'/Game/Blueprints/Curves/Curve_InterpRotation.Curve_InterpRotation'")
	UPROPERTY(EditAnywhere, Category = "Sliding|Rotation")
	UCurveFloat* InterpRotation = nullptr;

protected:
	UPROPERTY(EditAnywhere, Category = "Sliding|Montage")
	UAnimMontage* SlidingMontage; 

	UPROPERTY(EditAnywhere, Category = "Sliding|Montage")
	UAnimMontage* SlidingEndMontage;

protected:
	UFUNCTION()
	void Slide();

	UFUNCTION()
	void RevertCapsule();
};
