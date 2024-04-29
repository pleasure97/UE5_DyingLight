// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UE5_DyingLight/UE5_DyingLightGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUE5_DyingLightGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UE5_DYINGLIGHT_API UClass* Z_Construct_UClass_AUE5_DyingLightGameMode();
	UE5_DYINGLIGHT_API UClass* Z_Construct_UClass_AUE5_DyingLightGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_UE5_DyingLight();
// End Cross Module References
	void AUE5_DyingLightGameMode::StaticRegisterNativesAUE5_DyingLightGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AUE5_DyingLightGameMode);
	UClass* Z_Construct_UClass_AUE5_DyingLightGameMode_NoRegister()
	{
		return AUE5_DyingLightGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AUE5_DyingLightGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AUE5_DyingLightGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_UE5_DyingLight,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AUE5_DyingLightGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AUE5_DyingLightGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "UE5_DyingLightGameMode.h" },
		{ "ModuleRelativePath", "UE5_DyingLightGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AUE5_DyingLightGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AUE5_DyingLightGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AUE5_DyingLightGameMode_Statics::ClassParams = {
		&AUE5_DyingLightGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AUE5_DyingLightGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AUE5_DyingLightGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AUE5_DyingLightGameMode()
	{
		if (!Z_Registration_Info_UClass_AUE5_DyingLightGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AUE5_DyingLightGameMode.OuterSingleton, Z_Construct_UClass_AUE5_DyingLightGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AUE5_DyingLightGameMode.OuterSingleton;
	}
	template<> UE5_DYINGLIGHT_API UClass* StaticClass<AUE5_DyingLightGameMode>()
	{
		return AUE5_DyingLightGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUE5_DyingLightGameMode);
	AUE5_DyingLightGameMode::~AUE5_DyingLightGameMode() {}
	struct Z_CompiledInDeferFile_FID_UE5_DyingLight_Source_UE5_DyingLight_UE5_DyingLightGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UE5_DyingLight_Source_UE5_DyingLight_UE5_DyingLightGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AUE5_DyingLightGameMode, AUE5_DyingLightGameMode::StaticClass, TEXT("AUE5_DyingLightGameMode"), &Z_Registration_Info_UClass_AUE5_DyingLightGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AUE5_DyingLightGameMode), 3401414984U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UE5_DyingLight_Source_UE5_DyingLight_UE5_DyingLightGameMode_h_288226133(TEXT("/Script/UE5_DyingLight"),
		Z_CompiledInDeferFile_FID_UE5_DyingLight_Source_UE5_DyingLight_UE5_DyingLightGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UE5_DyingLight_Source_UE5_DyingLight_UE5_DyingLightGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
