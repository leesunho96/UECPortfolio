#include "WeaponDoActionData.h"
#include "DetailWidgetRow.h"

#include "SWeaponCheckBoxes.h"

TArray<TSharedPtr<SWeaponCheckBoxes>> FWeaponDoActionData::CheckBoxes;

TSharedRef<IPropertyTypeCustomization> FWeaponDoActionData::MakeInstance()
{
	return MakeShareable(new FWeaponDoActionData());
}

TSharedPtr<SWeaponCheckBoxes> FWeaponDoActionData::AddCheckBoxes()
{
	TSharedPtr<SWeaponCheckBoxes> checkBoxes = MakeShareable(new SWeaponCheckBoxes());
	int32 index = CheckBoxes.Add(checkBoxes);

	return CheckBoxes[index];
}

void FWeaponDoActionData::ClearCheckBoxes()
{
	for (TSharedPtr<SWeaponCheckBoxes> ptr : CheckBoxes)
	{
		if (ptr.IsValid())
			ptr.Reset();
	}

	CheckBoxes.Empty();
}

void FWeaponDoActionData::CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils)
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

void FWeaponDoActionData::CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils)
{
	if (CheckBoxes.Num() > 0)
	{
		int32 index = InPropertyHandle->GetIndexInArray();

		CheckBoxes[index]->DrawProperties(InPropertyHandle, &InChildBuilder);
	}
}