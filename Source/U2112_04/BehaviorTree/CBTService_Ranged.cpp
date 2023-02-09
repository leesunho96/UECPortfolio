#include "BehaviorTree/CBTService_Ranged.h"
#include "Global.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CPlayer.h"
#include "Components/CStateComponent.h"
#include "Components/CAIStateComponent.h"

UCBTService_Ranged::UCBTService_Ranged()
{
	NodeName = "Ranged";

	Interval = 0.1f;
	RandomDeviation = 0.0f;
}

void UCBTService_Ranged::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	UCAIStateComponent* aiState = CHelpers::GetComponent<UCAIStateComponent>(ai);

	if (state->IsHittedMode())
	{
		aiState->SetHittedMode();

		return;
	}

	ACPlayer* player = aiState->GetTargetPlayer();
	if (player == nullptr)
	{
		controller->ClearFocus(EAIFocusPriority::Gameplay);
		aiState->SetWaitMode();

		return;
	}

	controller->SetFocus(player);


	float distance = ai->GetDistanceTo(player);
	if (distance < AvoidRange)
	{
		aiState->SetAvoidMode();

		return;
	}

	aiState->SetActionMode();
}
