#pragma once

#include "CoreMinimal.h"
#include "Weapons/CSubAction.h"
#include "Weapons/CWeaponStructures.h"
#include "CSubAction_Thorn.generated.h"

UCLASS(Blueprintable)
class U2112_04_API UCSubAction_Thorn : public UCSubAction
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "FallObject")
		TSubclassOf<class ACThornObject> ObjectClass;

	UPROPERTY(EditDefaultsOnly, Category = "FallObject")
		FVector ObjectLocation;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
		FDoActionData ActionData;

public:
	UCSubAction_Thorn();

public:
	virtual void Pressed() override;

	virtual void Begin_SubAction_Implementation() override;
	virtual void End_SubAction_Implementation() override;
};
