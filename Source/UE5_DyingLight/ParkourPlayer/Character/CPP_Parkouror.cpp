// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/Character/CPP_Parkouror.h"
#include "GameFramework/CharacterMovementComponent.h"

ACPP_Parkouror::ACPP_Parkouror(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(Super::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACPP_Parkouror::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;

	if (DataTableRowHandle.IsNull()) { return; }
	if (DataTableRowHandle.RowName == NAME_None) { return; }

	CharacterDataTableRow = DataTableRowHandle.GetRow<FCharacterDataTableRow>(TEXT(""));
	GetMesh()->SetSkeletalMesh(CharacterDataTableRow->SkeletalMesh);
	GetMesh()->SetRelativeTransform(CharacterDataTableRow->SkeletalMeshTransform);
	GetMesh()->SetAnimClass(CharacterDataTableRow->AnimClass);

}



void ACPP_Parkouror::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetData(DataTableRowHandle);
}

// Called when the game starts or when spawned
void ACPP_Parkouror::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACPP_Parkouror::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_Parkouror::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}