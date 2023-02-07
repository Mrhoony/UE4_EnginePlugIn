#include "MeshViewer.h"

TSharedPtr<FMeshViewer> FMeshViewer::Instance = nullptr;
const static FName ToolkitName = TEXT("MeshViewer");
const static FName ViewportTabId = TEXT("Viewport");
const static FName PreviewTabId = TEXT("Preview");
const static FName DetailsTabId = TEXT("Detail");

void FMeshViewer::OpenWindow(UObject* InAsset)
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}
	Instance = MakeShareable<FMeshViewer>(new FMeshViewer());
	Instance->Open(InAsset);
}

void FMeshViewer::ShutDown()
{
	/*if (Instance.IsValid())
		Instance.Reset();*/
}

FName FMeshViewer::GetToolkitFName() const
{
	return ToolkitName;
}

FText FMeshViewer::GetBaseToolkitName() const
{
	return FText::FromName(ToolkitName);
}

FString FMeshViewer::GetWorldCentricTabPrefix() const
{
	return ToolkitName.ToString();
}

FLinearColor FMeshViewer::GetWorldCentricTabColorScale() const
{
	return FLinearColor::Red;
}

void FMeshViewer::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	FOnSpawnTab tab = FOnSpawnTab::CreateSP(this, &FMeshViewer::Spawn_ViewportTab);
	TabManager->RegisterTabSpawner(ViewportTabId, tab);
}

void FMeshViewer::Open(UObject* InAsset)
{
	Viewport = SNew(SMeshViewer_Viewport);

	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("MeshViewer_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(EOrientation::Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			// MainSplit
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(EOrientation::Orient_Horizontal)
				->SetSizeCoefficient(0.75f)
				->Split
				(
					FTabManager::NewStack()
					->AddTab(ViewportTabId, ETabState::OpenedTab)
				)
				// DescPanel
				->Split
				(
					FTabManager::NewSplitter()->SetOrientation(EOrientation::Orient_Vertical)
					->SetSizeCoefficient(0.25f)
					// Preview
					->Split
					(
						FTabManager::NewStack()
						->AddTab(PreviewTabId, ETabState::OpenedTab)
					)// Preview
					// Detail
					->Split 
					(
						FTabManager::NewStack()
						->AddTab(DetailsTabId, ETabState::OpenedTab)
					)// Detail
				)// DescPanel
			)// MainSplit
		);

	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, TSharedPtr<IToolkitHost>(), ToolkitName, layout, true, true, InAsset);
}

TSharedRef<SDockTab> FMeshViewer::Spawn_ViewportTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			Viewport.ToSharedRef()
		];
}
