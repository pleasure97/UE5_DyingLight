// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5_DyingLight : ModuleRules
{
	public UE5_DyingLight(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{ "Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"CableComponent",
			"AIModule",
			"MotionWarping"
		});

        PublicIncludePaths.Add("UE5_DyingLight");
        PublicIncludePaths.Add("UE5_DyingLight/ParkourPlayer");
	}
}
