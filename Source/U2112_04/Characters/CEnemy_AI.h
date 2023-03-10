#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy.h"
#include "CEnemy_AI.generated.h"

UCLASS()
class U2112_04_API ACEnemy_AI : public ACEnemy
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 2;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCAIStateComponent* AIState;

public:
	FORCEINLINE uint8 GetTeamID() { return TeamID; }

	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	
public:
	ACEnemy_AI();

protected:
	virtual void BeginPlay() override;
};
