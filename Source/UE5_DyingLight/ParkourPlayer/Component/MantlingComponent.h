// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MotionWarpingComponent.h"
#include "MantlingComponent.generated.h"

USTRUCT()
struct FMantlePosStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FVector MantlePos1; 
	
	UPROPERTY(EditAnywhere)
	FVector MantlePos2; 
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DYINGLIGHT_API UMantlingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMantlingComponent();

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
	UMotionWarpingComponent* MotionWarping = nullptr; 

protected:
	UPROPERTY(EditAnywhere, Category="Mantling")
	bool CanMantle = false; 

protected:
	UFUNCTION()
	void Mantle(); 

	UFUNCTION()
	FMantlePosStruct TraceMantle(float InitialTraceLength, float SecondaryTraceZOffset, float FallingHeightMultiplier);

	UFUNCTION()
	void PlayMantle(FVector Location1, FVector Location2, float ZOffsetHand, float ZOffsetLanding, float MontageLength); 

};
