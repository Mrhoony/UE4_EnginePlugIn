#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class TOY_API FMeshActor_DetailPanel : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override; // Slate UI SYNTAX 사용 예정

private:
	FReply OnClicked_ShuffleMaterial();

	TArray<TWeakObjectPtr<UObject>> Objects;
};
