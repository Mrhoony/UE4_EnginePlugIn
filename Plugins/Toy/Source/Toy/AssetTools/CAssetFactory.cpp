#include "CAssetFactory.h"
#include "CAsset.h"

UCAssetFactory::UCAssetFactory()
{
	bCreateNew = true;	// 신규생성을 가능하게 하는 변수
	bEditAfterNew = true; // 편집 필드를 열어주는 변수
	SupportedClass = UCAsset::StaticClass(); // 팩토리로 만들때 필요한 클래스 레퍼런스
}

UObject* UCAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UCAsset>(InParent, InName, Flags);
}
