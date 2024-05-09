// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "CableComponent.h"
#include "Components/TimelineComponent.h"
#include "GrapplingRopeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DYINGLIGHT_API UGrapplingRopeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrapplingRopeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Grapple Hook")
	bool CanGrappleHook = true;

	UPROPERTY(EditAnywhere, Category = "Grapple Hook")
	float GrappleHookDistance = 1500.f;

	UPROPERTY(EditAnywhere, Category = "Grapple Hook")
	FVector HookLocation;

	UPROPERTY(EditAnywhere, Category = "Grapple Hook")
	float GrappleHookCoolDown = 1.f;

	UPROPERTY(EditAnywhere, Category = "Grapple Hook")
	bool GrappleHookEnabled = true;

protected:
	UPROPERTY(EditAnywhere, Category = "Grapple Timeline")
	UTimelineComponent* GrappleShootTimeline = nullptr;

	UPROPERTY(EditAnywhere, Category = "Grapple Timeline")
	UCurveFloat* InterpSpeed = nullptr;
	

protected:
	UFUNCTION()
	void GrappleHook(); 
	
};
