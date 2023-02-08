// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Toy : ModuleRules
{
	public Toy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		//PrivateIncludePaths.Add(ModuleDirectory);
		PublicIncludePaths.Add(ModuleDirectory); // 프로젝트 내 다른 모듈들에서도 접근이 허용됨
			
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"EditorStyle",
			"Game",
			"Projects",
			"GameplayDebugger",
			"PropertyEditor",
			"MainFrame",
			"DesktopPlatform",
			"UnrealEd",
			"AdvancedPreviewScene",
			"InputCore",
			"AssetTools"
		});
	}
}
