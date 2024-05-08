// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer/Data/Input/BasicInputDataConfig.h"

UBasicInputDataConfig::UBasicInputDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("Script/EnhancedInput.InputMappingContext'/Game/ThirdPerson/Input/IMC_Default'") };
		check(Asset.Succeeded());
		InputMappingContext = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Move'") };
		check(Asset.Succeeded());
		Move = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Look'") };
		check(Asset.Succeeded());
		Look = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Jump'") };
		check(Asset.Succeeded());
		Jump = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_GrappleRope'") };
		check(Asset.Succeeded());
		GrappleRope = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Slide'") };
		check(Asset.Succeeded());
		Slide = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Mantle'") };
		check(Asset.Succeeded());
		Mantle = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Sprint'") };
		check(Asset.Succeeded());
		Sprint = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_DropKick'") };
		check(Asset.Succeeded());
		DropKick = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Attack'") };
		check(Asset.Succeeded());
		Attack = Asset.Object;
	}

}
