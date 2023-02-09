#include "WeaponDetailsView.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"

#include "WeaponEquipmentData.h"
#include "WeaponDoActionData.h"
#include "WeaponHitData.h"
#include "SWeaponCheckBoxes.h"
#include "Weapons/CWeaponAsset.h"
#include "Weapons/CWeaponStructures.h"

#include "Animation/AnimMontage.h"
#include "Sound/SoundWave.h"
#include "Particles/ParticleSystem.h"

bool FWeaponDetailsView::RefreshByCheckBoxes = false;

TSharedRef<IDetailCustomization> FWeaponDetailsView::MakeInstance()
{
	return MakeShareable(new FWeaponDetailsView());
}

void FWeaponDetailsView::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	Type = UCWeaponAsset::StaticClass();

	//Attachment
	{
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("Attachment", FText::FromName("Attachment"));
		category.AddProperty("AttachmentClass", Type);
	}
	
	//Equipment
	{
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("Equipment", FText::FromName("Equipment"));
		IDetailPropertyRow& row = category.AddProperty("EquipmentData", Type);

		if (RefreshByCheckBoxes == false)
		{
			FWeaponEquipmentData::RemoveCheckBoxes();
			TSharedPtr<SWeaponCheckBoxes> checkBoxes = FWeaponEquipmentData::CreateCheckBoxes();

			int32 index = 0;
			checkBoxes->Add("Montage", row.GetPropertyHandle()->GetChildHandle((uint32)index++));
			checkBoxes->Add("PlayRatio", row.GetPropertyHandle()->GetChildHandle((uint32)index++));
			checkBoxes->Add("CanMove", row.GetPropertyHandle()->GetChildHandle((uint32)index++));
			checkBoxes->Add("ControlRotation", row.GetPropertyHandle()->GetChildHandle((uint32)index++));

			index = 0;
			FEquipmentData data;
			checkBoxes->CheckDefaultObject(index++, data.Montage);
			checkBoxes->CheckDefaultValue(index++, data.PlayRatio);
			checkBoxes->CheckDefaultValue(index++, data.bCanMove);
			checkBoxes->CheckDefaultValue(index++, data.bUseControlRotation);
		}
	}

	//DoAction
	{
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("DoAction", FText::FromName("DoAction"));
		category.AddProperty("DoActionClass", Type);

		
		IDetailPropertyRow& actionRow = category.AddProperty("DoActionDatas", Type);
		if (RefreshByCheckBoxes == false)
		{
			uint32 count = 0;
			actionRow.GetPropertyHandle()->GetNumChildren(count);

			FWeaponDoActionData::ClearCheckBoxes();

			FDoActionData data;
			for (uint32 i = 0; i < count; i++)
			{
				TSharedPtr<SWeaponCheckBoxes> checkBoxes = FWeaponDoActionData::AddCheckBoxes();

				TSharedPtr<IPropertyHandle> handle = actionRow.GetPropertyHandle()->GetChildHandle(i);


				int32 index = 0;
				checkBoxes->Add("Montage", handle->GetChildHandle((uint32)index++));
				checkBoxes->Add("PlayRatio", handle->GetChildHandle((uint32)index++));
				checkBoxes->Add("CanMove", handle->GetChildHandle((uint32)index++));
				checkBoxes->Add("FixedCamera", handle->GetChildHandle((uint32)index++));
				

				index = 0;
				checkBoxes->CheckDefaultObject(index++, data.Montage);
				checkBoxes->CheckDefaultValue(index++, data.PlayRatio);
				checkBoxes->CheckDefaultValue(index++, data.bCanMove);
				checkBoxes->CheckDefaultValue(index++, data.bFixedCamera);
			}
		}//if (RefreshByCheckBoxes)


		IDetailPropertyRow& hitRow = category.AddProperty("HitDatas", Type);
		if (RefreshByCheckBoxes == false)
		{
			uint32 count = 0;
			hitRow.GetPropertyHandle()->GetNumChildren(count);

			FWeaponHitData::ClearCheckBoxes();

			FHitData data;
			for (uint32 i = 0; i < count; i++)
			{
				TSharedPtr<SWeaponCheckBoxes> checkBoxes = FWeaponHitData::AddCheckBoxes();
				TSharedPtr<IPropertyHandle> handle = hitRow.GetPropertyHandle()->GetChildHandle(i);

				int32 index = 0;
				checkBoxes->Add("Montage", handle->GetChildHandle((uint32)index++));
				checkBoxes->Add("PlayRatio", handle->GetChildHandle((uint32)index++));
				checkBoxes->Add("Power", handle->GetChildHandle((uint32)index++));
				checkBoxes->Add("Launch", handle->GetChildHandle((uint32)index++));
				checkBoxes->Add("StopTime", handle->GetChildHandle((uint32)index++));
				checkBoxes->Add("Sound", handle->GetChildHandle((uint32)index++));
				checkBoxes->Add("Effect", handle->GetChildHandle((uint32)index++));
				checkBoxes->Add("EffectLocation", handle->GetChildHandle((uint32)index++));
				checkBoxes->Add("EffectScale", handle->GetChildHandle((uint32)index++));

				index = 0;
				checkBoxes->CheckDefaultObject(index++, data.Montage);
				checkBoxes->CheckDefaultValue(index++, data.PlayRatio);
				checkBoxes->CheckDefaultValue(index++, data.Power);
				checkBoxes->CheckDefaultValue(index++, data.Launch);
				checkBoxes->CheckDefaultValue(index++, data.StopTime);
				checkBoxes->CheckDefaultObject(index++, data.Sound);
				checkBoxes->CheckDefaultObject(index++, data.Effect);
				checkBoxes->CheckDefaultValue(index++, data.EffectLocation);
				checkBoxes->CheckDefaultValue(index++, data.EffectScale);
			}
		}//if (RefreshByCheckBoxes)
	}

	//Attachment
	{
		IDetailCategoryBuilder& category = DetailBuilder.EditCategory("SubAction", FText::FromName("SubAction"));
		category.AddProperty("SubActionClass", Type);
	}
}