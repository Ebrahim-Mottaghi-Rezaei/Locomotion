// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Locomotion : ModuleRules {
    public Locomotion(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { });

        PrivateIncludePaths.AddRange(new string[] { });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "InputCore", "Engine", "UMG", "Slate", "SlateCore", "AnimGraphRuntime", "AIModule", "ClothingSystemRuntimeNv" });

        PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "Slate", "SlateCore" });

        DynamicallyLoadedModuleNames.AddRange(new string[] { });
    }
}