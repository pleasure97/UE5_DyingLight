// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_Parkouror.generated.h"


USTRUCT()
struct FCharacterDataTableRow : public FTableRowBase
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, Category = "Character")
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "Character")
	FTransform SkeletalMeshTransform;

	UPROPERTY(EditAnywhere, Category = "Character")
	TSubclassOf<UAnimInstance> AnimClass;
};
UCLASS()
class UE5_DYINGLIGHT_API ACPP_Parkouror : public ACharacter
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void Warping();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartParkour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MiddleParkour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LastParkour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanHanging;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SideMove;


public:
	// Sets default values for this character's properties
	ACPP_Parkouror(const FObjectInitializer& ObjectInitializer);

	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);

protected:

	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/"))
	FDataTableRowHandle DataTableRowHandle;
	FCharacterDataTableRow* CharacterDataTableRow = nullptr;
};
