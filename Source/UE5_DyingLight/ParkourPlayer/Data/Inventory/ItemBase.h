// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnumItemCategory.h"
#include "EnumRarityTag.h"
#include "Item.h"
#include "ItemBase.generated.h"

/**
 * 
 */
USTRUCT()
struct UE5_DYINGLIGHT_API FItemBase : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AItem> ItemClass;

	UPROPERTY(EditAnywhere)
	int Code;

	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText Lore;

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
	int Stack;

	UPROPERTY(EditAnywhere)
	EnumRarityTag Rarity;

	UPROPERTY(EditAnywhere)
	FColor RarityColor;

	// Armor Toggle And Setting
	UPROPERTY(EditAnywhere)
	bool IsEquipment;

	UPROPERTY(EditAnywhere)
	int ArmorDefense;

	// Weapon Toggle And Setting
	UPROPERTY(EditAnywhere)
	bool IsWeapon;

	UPROPERTY(EditAnywhere)
	int MinDamage;

	UPROPERTY(EditAnywhere)
	int MaxDamage;

	UPROPERTY(EditAnywhere)
	int AttackRate;

	// Is Use Duraility And Value
	UPROPERTY(EditAnywhere)
	bool IsDuraility;

	UPROPERTY(EditAnywhere)
	float Duraility;

	UPROPERTY(EditAnywhere)
	EnumItemCategory Category;
};
