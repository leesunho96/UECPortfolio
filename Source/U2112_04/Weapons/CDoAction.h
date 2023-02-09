#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Weapons/CWeaponStructures.h"
#include "CDoAction.generated.h"

UCLASS(Abstract)
class U2112_04_API UCDoAction : public UObject
{
	GENERATED_BODY()
	
public:
	FORCEINLINE bool GetBeginAction() { return bBeginAction; }

public:
	UCDoAction();

	virtual void BeginPlay(class ACAttachment* InAttachment, class UCEquipment* InEquipment, class ACharacter* InOwner, const TArray<FDoActionData>& InDoActionDatas, const TArray<FHitData>& InHitDatas);
	virtual void Tick(float InDeltaTime);

public:
	virtual void DoAction();
	virtual void Begin_DoAction();
	virtual void End_DoAction();

public:
	UFUNCTION()
		virtual void OnAttachmentCollision() { }

	UFUNCTION()
		virtual void OffAttachmentCollision() { }

	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class UShapeComponent* InCollision, class ACharacter* InOther) { }
	
	UFUNCTION()
		virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class UShapeComponent* InCollision, class ACharacter* InOther) { }

protected:
	class ACharacter* Owner;
	class UWorld* World;

	class UCStateComponent* State;
	class UCMoveComponent* Move;

protected:
	bool bDoingAction;
	bool bBeginAction;

	TArray<FDoActionData> DoActionDatas;
	TArray<FHitData> HitDatas;
};
