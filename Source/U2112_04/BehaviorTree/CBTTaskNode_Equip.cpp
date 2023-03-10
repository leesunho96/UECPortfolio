#include "BehaviorTree/CBTTaskNode_Equip.h"
#include "Global.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CAIController.h"
#include "Components/CStateComponent.h"
#include "Weapons/CEquipment.h"

UCBTTaskNode_Equip::UCBTTaskNode_Equip()
{
	NodeName = "Equip";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Equip::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	
	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	CheckNullResult(weapon, EBTNodeResult::Failed);

	if (Type == weapon->GetWeaponType())
		return EBTNodeResult::Succeeded;

	switch (Type)
	{
		case EWeaponType::Sword: weapon->SetSwordMode(); break;
		case EWeaponType::Rotator: weapon->SetRotatorMode(); break;
		case EWeaponType::Warp: weapon->SetWarpMode(); break;
	}


	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Equip::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	if (state->IsIdleMode())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		return;
	}
}

EBTNodeResult::Type UCBTTaskNode_Equip::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(ai);
	if (weapon == nullptr)
	{
		FinishLatentAbort(OwnerComp);

		return EBTNodeResult::Failed;
	}

	bool bBegin = weapon->GetEquipment()->GetBeginEquip();
	if (bBegin == false)
		weapon->GetEquipment()->Begin_Equip();
	
	weapon->GetEquipment()->End_Equip();

	FinishLatentAbort(OwnerComp);
	return EBTNodeResult::Succeeded;
}

