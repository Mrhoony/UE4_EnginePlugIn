#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

struct FBinaryData
{
	TArray<FVector> Positions;
	TArray<FVector> Normals;
	TArray<FColor> Colors;
	TArray<FVector2D> UVs;
	TArray<int32> Indices;

	friend FArchive& operator <<(FArchive& InArchive, FBinaryData InData)
	{
		return InArchive
			<< InData.Positions
			<< InData.Normals
			<< InData.Colors
			<< InData.UVs
			<< InData.Indices;
	}
};

class TOY_API FMeshActor_DetailPanel : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override; // Slate UI SYNTAX 사용 예정

private:
	FReply OnClicked_ShuffleMaterial();
	FReply OnClicked_SaveMesh();

	TArray<TWeakObjectPtr<UObject>> Objects;
};
