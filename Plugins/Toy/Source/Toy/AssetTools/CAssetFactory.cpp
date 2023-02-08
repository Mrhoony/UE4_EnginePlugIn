#include "CAssetFactory.h"
#include "CAsset.h"

UCAssetFactory::UCAssetFactory()
{
	bCreateNew = true;	// �űԻ����� �����ϰ� �ϴ� ����
	bEditAfterNew = true; // ���� �ʵ带 �����ִ� ����
	SupportedClass = UCAsset::StaticClass(); // ���丮�� ���鶧 �ʿ��� Ŭ���� ���۷���
}

UObject* UCAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UCAsset>(InParent, InName, Flags);
}
