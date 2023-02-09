#include "AssetTypeActions_Weapon.h"
#include "WeaponAssetEditor.h"
#include "Weapons/CWeaponAsset.h"

FAssetTypeActions_Weapon::FAssetTypeActions_Weapon(EAssetTypeCategories::Type InCategory)
{
	Category = InCategory;
}

FText FAssetTypeActions_Weapon::GetName() const
{
	return FText::FromString("Asset");
}

UClass* FAssetTypeActions_Weapon::GetSupportedClass() const
{
	return UCWeaponAsset::StaticClass();
}

FColor FAssetTypeActions_Weapon::GetTypeColor() const
{
	return FColor::Black;
}

uint32 FAssetTypeActions_Weapon::GetCategories()
{
	return Category;
}

void FAssetTypeActions_Weapon::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	if (InObjects.Num() < 1)
		return;

	FWeaponAssetEditor::OpenWindow(InObjects[0]->GetName());
}