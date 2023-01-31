#include "Toy.h"
#include "Toolbar/ButtonCommand.h"
#include "Toolbar/IconStyle.h"
#include "DebuggerCategory/DebuggerCategory.h"
#include "LevelEditor.h"
#include "GameplayDebugger.h"

#define LOCTEXT_NAMESPACE "FToyModule"
#define VIEW_UE4_ICON_RESOURCES 0

void FToyModule::StartupModule()
{
	// ToolBar
	{
		FIconStyle::Get(); // Create를 위한 호출
		FButtonCommand::Register();

		Extender = MakeShareable(new FExtender());

		FToolBarExtensionDelegate toolBarBuilderDelegate = FToolBarExtensionDelegate::CreateRaw(this, &FToyModule::AddToolBar);
		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().Command, toolBarBuilderDelegate);

		FToolBarExtensionDelegate toolBarBuilderDelegate2 = FToolBarExtensionDelegate::CreateRaw(this, &FToyModule::AddToolBar2);
		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().Command, toolBarBuilderDelegate2);

		FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
	}

	// DebuggerCategory
	{
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get();
		IGameplayDebugger::FOnGetCategory MakeCategoryDelegate = IGameplayDebugger::FOnGetCategory::CreateStatic(&FDebuggerCategory::MakeInstance);
		gameplayDebugger.Get().RegisterCategory("AwesomeData", MakeCategoryDelegate, EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
		gameplayDebugger.NotifyCategoriesChanged();
	}

#if VIEW_UE4_ICON_RESOURCES
	TArray<const FSlateBrush*> brushes;
	FEditorStyle::GetResources(brushes);
	for (const FSlateBrush* brush : brushes)
		GLog->Log(brush->GetResourceName().ToString());
#endif
}

void FToyModule::ShutdownModule()
{
	FIconStyle::Shutdown();

	if(IGameplayDebugger::IsAvailable())
		IGameplayDebugger::Get().UnregisterCategory("AwesomeData");
}

void FToyModule::AddToolBar(class FToolBarBuilder& InBuilder)
{
	InBuilder.AddSeparator();
	InBuilder.AddToolBarButton
	(
		FButtonCommand::Get().ID,
		NAME_None,
		FText::FromString("Load Mesh"),
		FText::FromString("Load Mesh Data"),
		FIconStyle::Get()->ToolBar_Icon
	);

	//버튼의 정의(버튼의 디자인, 버튼 눌렀을 때 액션..)
}

void FToyModule::AddToolBar2(class FToolBarBuilder& InBuilder)
{
	InBuilder.AddToolBarButton
	(
		FButtonCommand::Get().ID2,
		NAME_None,
		FText::FromString("Open Viewer"),
		FText::FromString("Open Viewer"),
		FIconStyle::Get()->ToolBar_Icon2
	);

	//버튼의 정의(버튼의 디자인, 버튼 눌렀을 때 액션..)
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToyModule, Toy)