// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AnimalIsland : ModuleRules
{
	public AnimalIsland(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "AnimalIsland" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "EnhancedInput" });
	}
}
