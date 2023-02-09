#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "SWeaponListView.h"

class WEAPON_API FWeaponAssetEditor
	: public FAssetEditorToolkit
{
public:
	static void OpenWindow(FString InAssetName = "");
	static void Shutdown();

private:
	void Open(FString InAssetName);

protected:
	bool OnRequestClose() override;

public:
	void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	FName GetToolkitFName() const override;
	FText GetBaseToolkitName() const override;
	FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

private:
	TSharedRef<SDockTab> Spawn_ListViewTab(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> Spawn_DetailsTab(const FSpawnTabArgs& InArgs);

private:
	void WeaponListViewSelectedItem(FWeaponRowDataPtr InPtr);

private:
	static TSharedPtr<FWeaponAssetEditor> Instance;

private:
	static const FName EditorName;
	static const FName ListViewTabId;
	static const FName DetailsTabId;

private:
	TSharedPtr<class SWeaponListView> ListView;
	TSharedPtr<class IDetailsView> DetailsView;
};

