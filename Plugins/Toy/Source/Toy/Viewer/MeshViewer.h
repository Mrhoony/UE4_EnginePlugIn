#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "MeshViewer_Viewport.h"

class TOY_API FMeshViewer : public FAssetEditorToolkit
{
public:
	static void OpenWindow(UObject* InAsset);
	static void ShutDown();

public:
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

private:
	void Open(UObject* InAsset);

	TSharedRef<SDockTab> Spawn_ViewportTab(const FSpawnTabArgs& InArgs);

private:
	static TSharedPtr<FMeshViewer> Instance;

private:
	TSharedPtr<class SMeshViewer_Viewport> Viewport;
};
