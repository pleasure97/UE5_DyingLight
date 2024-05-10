// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "Camera/CameraComponent.h"
#include "SprintingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DYINGLIGHT_API USprintingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USprintingComponent();

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
	UCameraComponent* FollowCamera = nullptr; 

	UPROPERTY()
	USkeletalMeshComponent* CharMesh = nullptr; 

protected:
	UPROPERTY(EditAnywhere, Category = "Sprinting")
	bool IsSprinting = false;

	UPROPERTY(EditAnywhere, Category = "Sprinting")
	bool DoOnce = true;

	UPROPERTY(EditAnywhere, Category = "Sprinting")
	float SprintSpeed = 700.f;

	UPROPERTY(EditAnywhere, Category = "Sprinting")
	float DefaultWalkSpeed = 500.f; 

	UPROPERTY(EditAnywhere, Category = "Sprinting")
	double TriggeredSeconds; 

protected:
	UPROPERTY(EditAnywhere, Category = "Sprinting|Timeline")
	UTimelineComponent* SprintingFOV = nullptr; 

protected:
	UPROPERTY(EditAnywhere, Category = "Sprinting|Montage")
	UAnimMontage* SprintingStopMontage;

protected:
	UFUNCTION()
	void SprintTriggered(); 

	UFUNCTION()
	void SprintStarted(); 

	UFUNCTION()
	void SprintCompleted(); 

	UFUNCTION()
	void UpdateFOV(float Value); 


};
