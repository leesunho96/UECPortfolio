#include "BehaviorTree/CBTService_Melee.h"
#include "Global.h"
#include "CPatrolComponent.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CPlayer.h"
#include "Components/CStateComponent.h"
#include "Components/CAIStateComponent.h"

UCBTService_Melee::UCBTService_Melee()
{
	NodeName = "Melee";

	Interval = 0.1f;
	RandomDeviation = 0.0f;
}

void UCBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
		UCPatrolComponent* patrol = CHelpers::GetComponent<UCPatrolComponent>(ai);
		if (!!patrol)
		{
			aiState->SetPatrolMode();

			return;
		}

		aiState->SetWaitMode();

		return;
	}

	float distance = ai->GetDistanceTo(player);
	if (distance < ActionRange)
	{
		aiState->SetActionMode();

		return;
	}

	aiState->SetApproachMode();
}