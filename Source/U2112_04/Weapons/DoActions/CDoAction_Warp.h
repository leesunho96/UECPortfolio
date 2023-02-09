#pragma once

#include "CoreMinimal.h"
#include "Weapons/CDoAction.h"
#include "CDoAction_Warp.generated.h"

UCLASS()
class U2112_04_API UCDoAction_Warp : public UCDoAction
{
	GENERATED_BODY()
	
public:
	void BeginPlay(class ACAttachment* InAttachment, class UCEquipment* InEquipment, class ACharacter* InOwner, const TArray<FDoActionData>& InDoActionDatas, const TArray<FHitData>& InHitDatas) override;

	void DoAction() override;
	void Begin_DoAction() override;

	void Tick(float InDeltaTime) override;

private:
	bool GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotation);

private:
	class APlayerController* PlayerController;
	class UDecalComponent* Decal;

private:
	class UCAIStateComponent* AIState;

private:
	FVector MoveToLocation;
};
