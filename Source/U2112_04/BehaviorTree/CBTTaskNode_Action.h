#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Action.generated.h"

UCLASS()
class U2112_04_API UCBTTaskNode_Action : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskNode_Action();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& Owner0Comp, uint8* NodeMemory) override;
};
