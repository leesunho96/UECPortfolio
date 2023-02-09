#include "Weapons/CEquipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CMoveComponent.h"
#include "Components/CStateComponent.h"

void UCEquipment::BeginPlay(ACharacter* InOwner, const FEquipmentData& InData)
{
	OwnerCharacter = InOwner;
	Data = InData;

	Move = CHelpers::GetComponent<UCMoveComponent>(OwnerCharacter);
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
}

void UCEquipment::Equip()
{
	State->SetEquipMode();

	if (Data.bCanMove == false)
		Move->Stop();

	if (Data.bUseControlRotation)
		Move->EnableControlRotation();


	if (!!Data.Montage)
	{
		OwnerCharacter->PlayAnimMontage(Data.Montage, Data.PlayRatio);
	}
	else
	{
		Begin_Equip();
		End_Equip();
	}
}

void UCEquipment::Begin_Equip()
{
	bBeginEquip = true;

	if (OnBeginEquip.IsBound())
		OnBeginEquip.Broadcast();
}

void UCEquipment::End_Equip()
{
	bBeginEquip = false;
	bEquipped = true;

	State->SetIdleMode();
	Move->Move();
}

void UCEquipment::Unequip()
{
	bEquipped = false;
	Move->DisableControlRotation();

	if (OnUnequip.IsBound())
		OnUnequip.Broadcast();
}