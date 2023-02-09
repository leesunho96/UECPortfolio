#include "BehaviorTree/CEnvQueryContext_Target.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UCEnvQueryContext_Target::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	ACEnemy_AI* ai = Cast<ACEnemy_AI>(QueryInstance.Owner.Get());
	ACAIController* controller = ai->GetController<ACAIController>();
	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
	AActor* actor = Cast<AActor>(blackboard->GetValueAsObject("Player"));

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, actor);
}