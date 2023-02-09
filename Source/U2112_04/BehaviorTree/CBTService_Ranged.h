#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Ranged.generated.h"

UCLASS()
class U2112_04_API UCBTService_Ranged : public UBTService
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Action")
		float AvoidRange = 500;

public:
	UCBTService_Ranged();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
