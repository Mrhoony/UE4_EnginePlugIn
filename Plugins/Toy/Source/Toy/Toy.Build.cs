// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Toy : ModuleRules
{
	public Toy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivateIncludePaths.Add(ModuleDirectory);
			
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
		});
			
		
		PrivateDependencyModuleNames.AddRange(new string[]{	// ���̺귯�� ���� �߰�			
			"Engine",
			"Slate",
			"SlateCore",
			"EditorStyle",
			"Projects",
			"GameplayDebugger",
			"PropertyEditor",
			"Game",
			"MainFrame",
			"DesktopPlatform",
			"UnrealEd",
			"CoreUObject"
		});
		
		
	}
}
