// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DataDrivenFPT : ModuleRules
{
	public DataDrivenFPT(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
