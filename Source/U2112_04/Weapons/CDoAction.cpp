#include "Weapons/CDoAction.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CMoveComponent.h"

UCDoAction::UCDoAction()
{

}

void UCDoAction::BeginPlay(ACAttachment* InAttachment, UCEquipment* InEquipment, ACharacter* InOwner, const TArray<FDoActionData>& InDoActionDatas, const TArray<FHitData>& InHitDatas)
{
	Owner = InOwner;
	World = Owner->GetWorld();

	State = CHelpers::GetComponent<UCStateComponent>(Owner);
	Move = CHelpers::GetComponent<UCMoveComponent>(Owner);

	DoActionDatas = InDoActionDatas;
	HitDatas = InHitDatas;
}

void UCDoAction::Tick(float InDeltaTime)
{

}

void UCDoAction::DoAction()
{
	bDoingAction = true;
}

void UCDoAction::Begin_DoAction()
{
	bBeginAction = true;
}

void UCDoAction::End_DoAction()
{
	bDoingAction = false;
	bBeginAction = false;

	State->SetIdleMode();
	Move->Move();
	Move->DisableFixedCamera();
}