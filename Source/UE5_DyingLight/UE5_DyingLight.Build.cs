// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5_DyingLight : ModuleRules
{
	public UE5_DyingLight(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
