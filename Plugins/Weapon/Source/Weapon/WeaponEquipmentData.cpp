#include "WeaponEquipmentData.h"
#include "DetailWidgetRow.h"

#include "SWeaponCheckBoxes.h"

TSharedPtr<class SWeaponCheckBoxes> FWeaponEquipmentData::CheckBoxes = nullptr;

TSharedRef<IPropertyTypeCustomization> FWeaponEquipmentData::MakeInstance()
{
	return MakeShareable(new FWeaponEquipmentData());
}

TSharedPtr<class SWeaponCheckBoxes> FWeaponEquipmentData::CreateCheckBoxes()
{
	return CheckBoxes = MakeShareable(new SWeaponCheckBoxes());
}

void FWeaponEquipmentData::RemoveCheckBoxes()
{
	if (CheckBoxes.IsValid())
	{
		CheckBoxes.Reset();
		CheckBoxes = nullptr;
	}
}

void FWeaponEquipmentData::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	CheckBoxes->SetUtilities(InCustomizationUtils.GetPropertyUtilities());

	InHeaderRow
	.DiffersFromDefault(false)
	.NameContent()
	[
		InPropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	[
		CheckBoxes->Draw()
	];
}

void FWeaponEquipmentData::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	CheckBoxes->DrawProperties(InPropertyHandle, &InChildBuilder);
}

