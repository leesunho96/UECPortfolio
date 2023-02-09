#include "WeaponAssetEditor.h"
#include "Widgets/Docking/SDockTab.h"

#include "WeaponDetailsView.h"
#include "WeaponEquipmentData.h"
#include "WeaponDoActionData.h"
#include "WeaponHitData.h"
#include "Weapons/CWeaponAsset.h"

const FName FWeaponAssetEditor::EditorName = "WeaponAssetEditor";
const FName FWeaponAssetEditor::ListViewTabId = "LiewView";
const FName FWeaponAssetEditor::DetailsTabId = "Details";

TSharedPtr<FWeaponAssetEditor> FWeaponAssetEditor::Instance = nullptr;

void FWeaponAssetEditor::OpenWindow(FString InAssetName)
{
	if (Instance.IsValid())
	{
		if (Instance->ListView.IsValid())
		{
			//창 열림, 리스트 뷰 아이템 선택
			FWeaponRowDataPtr ptr = nullptr;

			if (InAssetName.Len() > 0)
				ptr = Instance->ListView->GetRowDataPtrByName(InAssetName);

			if (ptr == nullptr)
				ptr = Instance->ListView->GetFirstDataPtr();

			Instance->ListView->SelectDataPtr(ptr->Asset);

			return;
		}
		else
		{
			//컨텐츠 브라우저 선택 상황
			Instance->CloseWindow();

			Instance.Reset();
			Instance = nullptr;
		}
	}

	Instance = MakeShareable(new FWeaponAssetEditor());
	Instance->Open(InAssetName);
}

void FWeaponAssetEditor::Open(FString InAssetName)
{
	ListView = SNew(SWeaponListView)
		.OnWeaponListViewSelectedItem(this, &FWeaponAssetEditor::WeaponListViewSelectedItem);


	FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	prop.RegisterCustomPropertyTypeLayout("EquipmentData", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FWeaponEquipmentData::MakeInstance));
	prop.RegisterCustomPropertyTypeLayout("DoActionData", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FWeaponDoActionData::MakeInstance));
	prop.RegisterCustomPropertyTypeLayout("HitData", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FWeaponHitData::MakeInstance));
	prop.NotifyCustomizationModuleChanged();

	FDetailsViewArgs args(false, false, true, FDetailsViewArgs::ObjectsUseNameArea);
	args.ViewIdentifier = "WeaponAssetEditorDetailsView";
	DetailsView = prop.CreateDetailView(args);

	FOnGetDetailCustomizationInstance detailsView = FOnGetDetailCustomizationInstance::CreateStatic(&FWeaponDetailsView::MakeInstance);
	DetailsView->SetGenericLayoutDetailsDelegate(detailsView);



	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("WeaponAssetEditor_Layout")
	->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.1f)
			->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
		)
		->Split
		(
			FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.175f)
				->AddTab(ListViewTabId, ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.725f)
				->AddTab(DetailsTabId, ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
		)
	);

	
	UCWeaponAsset* asset = nullptr;
	if (InAssetName.Len() > 0)
	{
		FWeaponRowDataPtr ptr = ListView->GetRowDataPtrByName(InAssetName);

		if (ListView->SelectedRowDataPtrName() == InAssetName)
			return;

		if (ptr.IsValid() == false)
			asset = ListView->GetFirstDataPtr()->Asset;
		else
			asset = ptr->Asset;
	}
	else
	{
		asset = ListView->GetFirstDataPtr()->Asset;
	}


	InitAssetEditor(EToolkitMode::Standalone, TSharedPtr<IToolkitHost>(), EditorName, layout, true, true, asset);

	//DetailsView->SetObject(asset);
	ListView->SelectDataPtr(asset);
}

bool FWeaponAssetEditor::OnRequestClose()
{
	FWeaponEquipmentData::RemoveCheckBoxes();
	FWeaponDoActionData::ClearCheckBoxes();
	FWeaponHitData::ClearCheckBoxes();

	if(DetailsView.IsValid())
	{
		if (!!GEditor && !!GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
			GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->NotifyAssetClosed(GetEditingObject(), this);
	}

	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		prop.UnregisterCustomPropertyTypeLayout("EquipmentData");
		prop.UnregisterCustomPropertyTypeLayout("DoActionData");
		prop.UnregisterCustomPropertyTypeLayout("HitData");
		prop.NotifyCustomizationModuleChanged();
	}

	if (ListView.IsValid())
		ListView.Reset();

	if (DetailsView.IsValid())
		DetailsView.Reset();

	return true;
}

void FWeaponAssetEditor::Shutdown()
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}
}

void FWeaponAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	FOnSpawnTab tab = FOnSpawnTab::CreateSP(this, &FWeaponAssetEditor::Spawn_ListViewTab);
	InTabManager->RegisterTabSpawner(ListViewTabId, tab);

	FOnSpawnTab tab2 = FOnSpawnTab::CreateSP(this, &FWeaponAssetEditor::Spawn_DetailsTab);
	InTabManager->RegisterTabSpawner(DetailsTabId, tab2);
}

TSharedRef<SDockTab> FWeaponAssetEditor::Spawn_ListViewTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
	.Content()
	[
		ListView.ToSharedRef()
	];
}

TSharedRef<SDockTab> FWeaponAssetEditor::Spawn_DetailsTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
	.Content()
	[
		DetailsView.ToSharedRef()
	];
}

FName FWeaponAssetEditor::GetToolkitFName() const
{
	return EditorName;
}

FText FWeaponAssetEditor::GetBaseToolkitName() const
{
	return FText::FromName(EditorName);
}

FString FWeaponAssetEditor::GetWorldCentricTabPrefix() const
{
	return EditorName.ToString();
}

FLinearColor FWeaponAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0, 0, 1);
}

void FWeaponAssetEditor::WeaponListViewSelectedItem(FWeaponRowDataPtr InPtr)
{
	if (InPtr == nullptr)
		return;

	if (!!GetEditingObject())
		RemoveEditingObject(GetEditingObject());

	AddEditingObject(InPtr->Asset);
	DetailsView->SetObject(InPtr->Asset);
}