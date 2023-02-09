#include "WeaponHitData.h"
#include "DetailWidgetRow.h"

#include "SWeaponCheckBoxes.h"

TArray<TSharedPtr<SWeaponCheckBoxes>> FWeaponHitData::CheckBoxes;

TSharedRef<IPropertyTypeCustomization> FWeaponHitData::MakeInstance()
{
	return MakeShareable(new FWeaponHitData());
}

TSharedPtr<SWeaponCheckBoxes> FWeaponHitData::AddCheckBoxes()
{
	TSharedPtr<SWeaponCheckBoxes> checkBoxes = MakeShareable(new SWeaponCheckBoxes());
	int32 index = CheckBoxes.Add(checkBoxes);

	return CheckBoxes[index];
}

void FWeaponHitData::ClearCheckBoxes()
{
	for (TSharedPtr<SWeaponCheckBoxes> ptr : CheckBoxes)
	{
		if (ptr.IsValid())
			ptr.Reset();
	}

	CheckBoxes.Empty();
}

void FWeaponHitData::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	if (CheckBoxes.Num() > 0)
	{
		int32 index = InPropertyHandle->GetIndexInArray();


		CheckBoxes[index]->SetUtilities(InCustomizationUtils.GetPropertyUtilities());

		InHeaderRow
		.DiffersFromDefault(false)
		.NameContent()
		[
			InPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		.MaxDesiredWidth(2000)
		[
			CheckBoxes[index]->Draw()
		];
	}
}

void FWeaponHitData::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	if (CheckBoxes.Num() > 0)
	{
		int32 index = InPropertyHandle->GetIndexInArray();

		CheckBoxes[index]->DrawProperties(InPropertyHandle, &InChildBuilder);
	}
}
