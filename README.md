# UE4_EnginePlugIn
### 내용
1. [툴바 커스텀버튼 추가](https://github.com/Mrhoony/UE4_EnginePlugIn/new/main?readme=1#%ED%88%B4%EB%B0%94-%EC%BB%A4%EC%8A%A4%ED%85%80%EB%B2%84%ED%8A%BC-%EC%B6%94%EA%B0%80)
2. [디버그 카테고리 커스터마이징](https://github.com/Mrhoony/UE4_EnginePlugIn/new/main?readme=1#%EB%94%94%EB%B2%84%EA%B7%B8-%EC%B9%B4%ED%85%8C%EA%B3%A0%EB%A6%AC-%EC%BB%A4%EC%8A%A4%ED%84%B0%EB%A7%88%EC%9D%B4%EC%A7%95)
3. [디테일패널 커스텀 카테고리 추가](https://github.com/Mrhoony/UE4_EnginePlugIn/new/main?readme=1#%EB%94%94%ED%85%8C%EC%9D%BC%ED%8C%A8%EB%84%90-%EC%BB%A4%EC%8A%A4%ED%85%80-%EC%B9%B4%ED%85%8C%EA%B3%A0%EB%A6%AC-%EC%B6%94%EA%B0%80)
4. [커스텀 메시뷰어 생성](https://github.com/Mrhoony/UE4_EnginePlugIn/new/main?readme=1#%EC%BB%A4%EC%8A%A4%ED%85%80-%EB%A9%94%EC%8B%9C%EB%B7%B0%EC%96%B4-%EC%83%9D%EC%84%B1)
5. [에셋툴 카테고리 커스터마이징](https://github.com/Mrhoony/UE4_EnginePlugIn/new/main?readme=1#%EC%97%90%EC%85%8B%ED%88%B4-%EC%B9%B4%ED%85%8C%EA%B3%A0%EB%A6%AC-%EC%BB%A4%EC%8A%A4%ED%84%B0%EB%A7%88%EC%9D%B4%EC%A7%95)
<br>

---

### 에디터 구성
엔진 커스터마이징 내용에 대한 소개에 앞서 먼저 `언리얼 에디터(=에디터)`에 대해서 알아야 할 내용들을 간단하게 소개하겠다.<br>

![01](https://user-images.githubusercontent.com/52897037/220164506-4fe7b9eb-4773-4fc4-b83d-5a5b6ad9eddf.PNG)<br>
위의 화면에는 빨간색 테두리의 창과 초록색 테두리의 창이 띄워져 있다.<br>
이러한 창을 언리얼에서는 `toolkit(=툴킷)`이라고 부른다.<br>

툴킷은 EToolkitMode::Type에 따라 2가지로 분류된다.<br>
- 빨간색 테두리 : WorldCentric, 에디터를 실행했을 때 처음 보여지는 메인 툴킷<br>
- 초록색 테두리 : Standalone, 블루프린트, 애니메이션, 스켈레탈메시 등 수정을 하기 위해 파일을 열었을 때 새로 뜨는 툴킷<br>

![02](https://user-images.githubusercontent.com/52897037/220166156-f18c47b5-bc49-4b9b-9888-012c387ab036.PNG)<br>
다음으로 툴킷 위에 보여지는 모든 UI를 `tab(=탭)`이란 명칭으로 부른다.<br>
위의 화면의 빨간색 네모 테두리들은 월드센트릭 툴킷에 붙어있는 탭들이다.<br>

![03](https://user-images.githubusercontent.com/52897037/220167606-9996b820-f36e-4754-a8c7-fb55ddb8a9f2.png)<br>
기본으로 제공되는 툴킷들의 경우 탭들이 기본적으로 숨어있다.<br>
우상단 노란색 삼각형을 클릭해서 숨겨진 탭들이 보이게 할 수 있고<br>
탭을 우클릭하여 탭숨김버튼을 눌러서 다시 탭을 숨길수도 있다.<br>
당연하게도 2개 이상 겹쳐져 있는 탭은 숨기기가 불가하다.<br>

![05](https://user-images.githubusercontent.com/52897037/220169196-386433ee-7ce6-4d86-9451-bee35dc32b74.PNG)<br>
마지막으로 엔진 커스터마이징 시 에디터 개인설정에서 UI 익스텐션 포인트 디스플레이를 켜준다.<br>
익스텐션 포인트는 탭 내부에 컨텐츠를 배치할 때 배치할 영역에 대한 좌표 개념으로 이해하면 편하다.<br>
이어지는 툴바에 커스텀버튼을 추가하는 부분에서 좌표 개념과 사용에 대해 설명해두었다.<br>
<br>

---

## 툴바 커스텀버튼 추가
![04](https://user-images.githubusercontent.com/52897037/220168478-cec92934-3fde-4429-910f-e2f3d3cf1051.PNG)<br>
툴바에 커스텀버튼을 추가해봤다.<br>
- Load Mesh : 바이너리로 저장된 스태틱 메시를 읽어와서 레벨에디터상에서 보고있는 화면 중심에 메시를 배치한다.<br>
- Open Viewer : 커스터마이징한 메시뷰어 툴킷을 연다.<br>

![06](https://user-images.githubusercontent.com/52897037/220170998-6ea22381-9f69-4a07-a632-5e577e4378b5.PNG)<br>
버튼에 사용할 아이콘파일은 플러그인폴더/Resources에 저장한다.<br>

```cpp
FIconStyle::FIconStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));

	FString path = IPluginManager::Get().FindPlugin("Toy")->GetBaseDir();
	path /=  "Resources";
	StyleSet->SetContentRoot(path);

	RegisterIcon("ToolBarIcon", path / "Icon.png", FVector2D(48), ToolBar_Icon);
	RegisterIcon("ToolBarIcon2", path / "Icon2.png", FVector2D(48), ToolBar_Icon2);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

void FIconStyle::RegisterIcon(const FString& InName, const FString& InPath, const FVector2D& InSize, FSlateIcon& OutIcon)
{
	FSlateImageBrush* brush = new FSlateImageBrush(InPath, InSize);

	FString name = StyleSetName.ToString() + "." + InName;
	StyleSet->Set(FName(name), brush);

	OutIcon = FSlateIcon(StyleSetName, FName(name));
}
```
저장된 아이콘은 바로 사용할 수는 없고 FSlateStyleSet에 등록을 해줘야 한다.<br>

```cpp
// ToolBar
	{
		FIconStyle::Get();
		FButtonCommand::Register();

		Extender = MakeShareable(new FExtender());

		FToolBarExtensionDelegate toolBarBuilderDelegate = FToolBarExtensionDelegate::CreateRaw(this, &FToyModule::AddToolBar);
		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().Command, toolBarBuilderDelegate);

		FToolBarExtensionDelegate toolBarBuilderDelegate2 = FToolBarExtensionDelegate::CreateRaw(this, &FToyModule::AddToolBar2);
		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().Command, toolBarBuilderDelegate2);

		FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
	}
```
툴바에 버튼을 추가하려면 FExtender::AddToolBarExtension()을 사용해야 한다.<br>
FExtender는 탭 내부에 배치될 컨텐츠의 등록과 삭제시 필요한 포인터 반환 등 컨텐츠를 관리한다.<br>
위에서 언급한 익스텐션 포인트의 쓰임은 여기서 볼 수 있는데<br>
AddToolBarextension()의 첫번째 파라메터에 배치할 익스텐션 포인트를 지정하고<br>
두번째 파라메터에 EExtensionHook을 이용해 전, 후, 첫번째와 같이 해당 포인트에서 어느 위치에 붙일 것인지 정할 수 있다.<br>
<br>

---

## 디버그 카테고리 커스터마이징
![07](https://user-images.githubusercontent.com/52897037/220175606-f65c08fc-a997-45e3-85b9-73eab3ada6ca.PNG)<br>
다음은 플레이어, 플레이어 전방에 있는 액터, 디버깅 지정된 액터의 위치를 수집해서 출력하는<br>
커스텀 디버그 카테고리를 생성해서 배치해보았다.<br>

```cpp
void FDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);

	FCanvasTileItem item(FVector2D(10), FVector2D(300, 215), FLinearColor(0, 0, 0, 0.5f));
	item.BlendMode = ESimpleElementBlendMode::SE_BLEND_AlphaBlend;
	CanvasContext.DrawItem(item, CanvasContext.CursorX, CanvasContext.CursorY);

	CanvasContext.Printf(FColor::Green, L"  -- Player Pawn -- ");
	CanvasContext.Printf(FColor::White, L"Name : %s", *PlayerPawnData.Name);
	CanvasContext.Printf(FColor::White, L"Location : %s", *PlayerPawnData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"Forward : %s", *PlayerPawnData.Forward.ToString());
	CanvasContext.Printf(FColor::White, L"");

	CanvasContext.Printf(FColor::Green, L"  -- Forward Actor -- ");
	CanvasContext.Printf(FColor::White, L"Name : %s", *ForwardActorData.Name);
	CanvasContext.Printf(FColor::White, L"Location : %s", *ForwardActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"Forward : %s", *ForwardActorData.Forward.ToString());
	CanvasContext.Printf(FColor::White, L"");

	CanvasContext.Printf(FColor::Green, L"  -- Debugger Actor -- ");
	CanvasContext.Printf(FColor::White, L"Name : %s", *DebuggerActorData.Name);
	CanvasContext.Printf(FColor::White, L"Location : %s", *DebuggerActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"Forward : %s", *DebuggerActorData.Forward.ToString());
}
```
수집된 데이터를 출력하는 코드는 다음과 같다.<br>
DrawData()라는 함수를 재정의해 원하는 출력을 만들 수 있다.<br>

```cpp
	{
		IGameplayDebugger& gameplayDeubgger = IGameplayDebugger::Get();
		IGameplayDebugger::FOnGetCategory makeCategoryDelegate = IGameplayDebugger::FOnGetCategory::CreateStatic(&FDebuggerCategory::MakeInstance);
		gameplayDeubgger.Get().RegisterCategory("AwesomeData", makeCategoryDelegate, EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
		gameplayDeubgger.NotifyCategoriesChanged();
	}
```
디버그 카테고리에 등록하는 것은 IGameplayDebugger를 이용한다.<br>
RegisterCategory()에서 카테고리명, 델리게이트, 카테고리 초기상태, 사용할 키패드 넘버를 입력해주면<Br>
커스터마이징된 디버그 카테고리를 사용할 수 있다.<br>
<br>

---

## 디테일패널 커스텀 카테고리 추가

![8](https://user-images.githubusercontent.com/52897037/220178761-c28bf3d6-842f-498e-83b1-531b4d3f55f4.PNG)<br>
블루프린트 등 액터를 수정할 때 뜨는 새로운 툴킷을 프로퍼티에디터라 하는데<br>
프로퍼티에디터의 우측에 디테일탭에 커스텀 카테고리 AwesomeCategory를 만들고<br>
- Shuffle 버튼 : 불러온 액터의 마테리얼을 무작위로 변경<br>
- Save To Binary File : 불러온 액터를 바이너리 형태의 파일로 저장<br>
2개의 버튼을 만들어 배치해주었다.<br>

```cpp
void FMeshActor_DetailPanel::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& cateory = DetailBuilder.EditCategory("Awesome Category");

	//Shuffle Material
	cateory.AddCustomRow(FText::FromString("Shuffle"))
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Material Instance"))
	]
	.ValueContent()
	.VAlign(VAlign_Center)
	.MaxDesiredWidth(250)
	[
		SNew(SButton)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Fill)
		.OnClicked(this, &FMeshActor_DetailPanel::OnClicked_ShuffleMaterial)
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Shuffle"))
		]
	];

	//Save Mesh
	cateory.AddCustomRow(FText::FromString("Save"))
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Save Mesh"))
	]
	.ValueContent()
	.VAlign(VAlign_Center)
	.MaxDesiredWidth(250)
	[
		SNew(SButton)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Fill)
		.OnClicked(this, &FMeshActor_DetailPanel::OnClicked_SaveMesh)
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Save To Binary File"))
		]
	];

	DetailBuilder.GetObjectsBeingCustomized(Objects);

}
```
디테일탭 내부에 부착할 컨텐츠를 생성하는 코드가 다소 생소한데<br>
엔진과 에디터를 수정하는데 사용되는 위와 같은 문법을 Slate(=슬레이트) 문법이라고 한다.<br>

```cpp
{
		FPropertyEditorModule& propertyEditor =  FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		propertyEditor.RegisterCustomClassLayout
		(
			ACMeshActor::StaticClass()->GetFName(),
			FOnGetDetailCustomizationInstance::CreateStatic(&FMeshActor_DetailPanel::MakeInstance)
		);
	}
```
FPropertyEditorModule를 이용해서 프로퍼티에디터를 호출하고<br>
지정된 액터가 호출된 경우 호출할 커스텀 디테일탭에 대한 델리게이트를 등록했다.<br>

---

## 커스텀 메시뷰어 생성

![09](https://user-images.githubusercontent.com/52897037/220182794-24b0181e-1b26-4645-b044-ef4beac43501.PNG)<br>
메인툴킷의 툴바에 생성해둔 커스텀버튼 Open Viewer를 눌렀을 시 호출되는 서브툴킷 메시뷰어를 생성했다.<br>
상단의 툴바, 좌측의 뷰포트, 우측의 프리뷰 세팅과 디테일 패널로 구성되어 있다.<br>

```cpp
void FMeshViewer::Open(UObject* InAsset)
{
	// Viewport
	Viewport = SNew(SMeshViewer_Viewport);

	// Preview
	FAdvancedPreviewSceneModule& scene = FModuleManager::LoadModuleChecked<FAdvancedPreviewSceneModule>("AdvancedPreviewScene");
	PreviewSceneSettings = scene.CreateAdvancedPreviewSceneSettingsWidget(Viewport->GetScene());

	// Detail
	FPropertyEditorModule& propertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs args(false, false, true, FDetailsViewArgs::ObjectsUseNameArea);
	DetailsView = propertyEditor.CreateDetailView(args);
	DetailsView->SetObject(InAsset);

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
```
메시뷰어를 구성하는 데에는 Split(=스플릿) 문법이 사용되었는데<br>
스플릿문법은 함수의 리턴이 자기자신인 점을 이용해 계속 꼬리물듯 함수를 호출하는 방식으로<br>
이를 Chaining(=체이닝) 기법이라고도 한다.<br>
눈여겨봐야 할 점은 메시뷰어의 탭을 추가할때는 2단계로 진행된다는 점인데<br>
첫번째로 Split()을 이용해 공간을 분할하고 두번째로 해당 공간에 탭을 추가한다는 점이다.<br>

<br>

---

## 에셋툴 카테고리 커스터마이징

![10](https://user-images.githubusercontent.com/52897037/220184133-7308e8ec-c007-4bb8-b5a1-745f710c3448.PNG)<br>
마지막으로 에셋툴에 커스텀 카테고리를 추가해보았다.<br>
에셋툴이란 컨텐츠 브라우저탭에서 마우스 우클릭을 했을 때 나오는 팝업메뉴이다.<br>
이 메뉴에 Awesome Category란 카테고리를 생성하고 클릭하면 Awesome Asset을 생성할 수 있게 코드를 작성했다.<br>

```cpp
{
		IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		//EAssetTypeCategories::Type category = EAssetTypeCategories::Misc;
		EAssetTypeCategories::Type category = assetTools.RegisterAdvancedAssetCategory(NAME_None, FText::FromString("Awesome Category"));
		Actions = MakeShareable(new CAssetAction(category));
		assetTools.RegisterAssetTypeActions(Actions.ToSharedRef());
	}
```
UAsset을 생성하고자 할 경우 UFactory에 정의되어 있는 가상함수들을 재정의해 사용한다.<br>
필요한 것은 총 3가지로 커스텀 카테고리, 에서 생성할 에셋, 을 생성할 함수 이다.<br>
에셋툴이 있는지 확인 후 불러와서 카테고리와 액션을 등록해주면 된다.<br>
