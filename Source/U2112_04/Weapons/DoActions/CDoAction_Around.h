#pragma once

#include "CoreMinimal.h"
#include "Weapons/CDoAction.h"
#include "CDoAction_Around.generated.h"

UCLASS(Blueprintable)
class U2112_04_API UCDoAction_Around : public UCDoAction
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Spawn")
		TArray<TSubclassOf<class ACRotator_Object>> RotatorObjectClasses;

public:
	void DoAction() override;
	void Begin_DoAction() override;
};
