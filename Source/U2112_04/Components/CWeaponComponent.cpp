#include "Components/CWeaponComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Weapons/CWeaponAsset.h"
#include "Weapons/CWeaponData.h"
#include "Weapons/CAttachment.h"
#include "Weapons/CEquipment.h"
#include "Weapons/CDoAction.h"
#include "Weapons/CSubAction.h"

UCWeaponComponent::UCWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());

	for (int i = 0; i < (int32)EWeaponType::Max; i++)
	{
		if (!!DataAssets[i])
			DataAssets[i]->BeginPlay(Owner, &Datas[i]);
	}
}

void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UCDoAction* action = GetDoAction();
	if (!!action)
		action->Tick(DeltaTime);

	if (!!GetSubAction())
		GetSubAction()->Tick(DeltaTime);
}

ACAttachment* UCWeaponComponent::GetAttachment()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	return Datas[(int32)Type]->GetAttachment();
}

UCEquipment* UCWeaponComponent::GetEquipment()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	return Datas[(int32)Type]->GetEquipment();
}

UCDoAction* UCWeaponComponent::GetDoAction()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	return Datas[(int32)Type]->GetDoAction();
}

UCSubAction* UCWeaponComponent::GetSubAction()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckNullResult(DataAssets[(int32)Type], nullptr);

	return Datas[(int32)Type]->GetSubAction();
}

void UCWeaponComponent::SetUnarmedMode()
{
	GetEquipment()->Unequip();
	ChangeType(EWeaponType::Max);
}

void UCWeaponComponent::SetFistMode()
{
	SetMode(EWeaponType::Fist);
}

void UCWeaponComponent::SetSwordMode()
{
	SetMode(EWeaponType::Sword);
}

void UCWeaponComponent::SetHammerMode()
{
	SetMode(EWeaponType::Hammer);
}

void UCWeaponComponent::SetWarpMode()
{
	SetMode(EWeaponType::Warp);
}

void UCWeaponComponent::SetRotatorMode()
{
	SetMode(EWeaponType::Rotator);
}

void UCWeaponComponent::SetBowMode()
{
	SetMode(EWeaponType::Bow);
}

void UCWeaponComponent::SetMode(EWeaponType InType)
{
	if (Type == InType)
	{
		SetUnarmedMode();

		return;
	}
	else if (IsUnarmedMode() == false)
	{
		GetEquipment()->Unequip();
	}

	if (!!DataAssets[(int32)InType])
	{
		Datas[(int32)InType]->GetEquipment()->Equip();

		ChangeType(InType);
	}
}

void UCWeaponComponent::ChangeType(EWeaponType InType)
{
	EWeaponType prevType = Type;
	Type = InType;

	if (OnWeaponTypeChange.IsBound())
		OnWeaponTypeChange.Broadcast(prevType, InType);
}

void UCWeaponComponent::DoAction()
{
	CheckTrue(IsUnarmedMode());

	if (!!GetDoAction())
		GetDoAction()->DoAction();
}

void UCWeaponComponent::SubAction_Pressed()
{
	if (!!GetSubAction())
		GetSubAction()->Pressed();
}

void UCWeaponComponent::SubAction_Released()
{
	if (!!GetSubAction())
		GetSubAction()->Released();
}