#include "Notifies/CAnimNotify_Begin_DoAction.h"
#include "Global.h"
#include "Components/CWeaponComponent.h"
#include "Weapons/CDoAction.h"

FString UCAnimNotify_Begin_DoAction::GetNotifyName_Implementation() const
{
	return "Begin_DoAction";
}

void UCAnimNotify_Begin_DoAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);
	CheckNull(weapon->GetDoAction());

	weapon->GetDoAction()->Begin_DoAction();
}