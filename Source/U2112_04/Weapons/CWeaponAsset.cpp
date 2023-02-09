#include "Weapons/CWeaponAsset.h"
#include "Global.h"
#include "CAttachment.h"
#include "CEquipment.h"
#include "CDoAction.h"
#include "CSubAction.h"
#include "CWeaponData.h"
#include "GameFramework/Character.h"

UCWeaponAsset::UCWeaponAsset()
{
	AttachmentClass = ACAttachment::StaticClass();
}

void UCWeaponAsset::BeginPlay(ACharacter* InOwner, UCWeaponData** OutWeaponData)
{
	ACAttachment* attachment = nullptr;
	if (!!AttachmentClass)
	{
		FActorSpawnParameters params;
		params.Owner = InOwner;

		attachment = InOwner->GetWorld()->SpawnActor<ACAttachment>(AttachmentClass, params);
	}

	
	UCEquipment* equipment = NewObject<UCEquipment>(this);
	equipment->BeginPlay(InOwner, EquipmentData);

	if (!!attachment)
	{
		equipment->OnBeginEquip.AddDynamic(attachment, &ACAttachment::OnBeginEquip);
		equipment->OnUnequip.AddDynamic(attachment, &ACAttachment::OnUnequip);
	}

	UCDoAction* doAction = nullptr;
	if (!!DoActionClass)
	{
		doAction = NewObject<UCDoAction>(this, DoActionClass);
		doAction->BeginPlay(attachment, equipment, InOwner, DoActionDatas, HitDatas);

		if (!!attachment)
		{
			attachment->OnAttachmentCollision.AddDynamic(doAction, &UCDoAction::OnAttachmentCollision);
			attachment->OffAttachmentCollision.AddDynamic(doAction, &UCDoAction::OffAttachmentCollision);

			attachment->OnAttachmentBeginOverlap.AddDynamic(doAction, &UCDoAction::OnAttachmentBeginOverlap);
			attachment->OnAttachmentEndOverlap.AddDynamic(doAction, &UCDoAction::OnAttachmentEndOverlap);
		}
	}

	UCSubAction* subAction = nullptr;
	if (!!SubActionClass)
	{
		subAction = NewObject<UCSubAction>(this, SubActionClass);
		subAction->BeginPlay(InOwner, attachment, doAction);
	}


	*OutWeaponData = NewObject<UCWeaponData>();
	(*OutWeaponData)->Attachment = attachment;
	(*OutWeaponData)->Equipment = equipment;
	(*OutWeaponData)->DoAction = doAction;
	(*OutWeaponData)->SubAction = subAction;
}

#if WITH_EDITOR
void UCWeaponAsset::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	CheckTrue(FApp::IsGame());
	
	//CLog::Log(PropertyChangedEvent.GetPropertyName().ToString());
	//CLog::Log((int32)PropertyChangedEvent.ChangeType);

	
	
	bool bRefresh = false;
	bRefresh |= PropertyChangedEvent.GetPropertyName().Compare("DoActionDatas") == 0;
	bRefresh |= PropertyChangedEvent.GetPropertyName().Compare("HitDatas") == 0;

	CheckFalse(bRefresh);


	bool bCheck = false;
	bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayAdd;
	bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayRemove;
	bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayClear;
	bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::Duplicate;

	CheckFalse(bCheck);


	FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	TSharedPtr<IDetailsView> detailsView = prop.FindDetailView("WeaponAssetEditorDetailsView");

	if (detailsView.IsValid())
		detailsView->ForceRefresh();
}
#endif