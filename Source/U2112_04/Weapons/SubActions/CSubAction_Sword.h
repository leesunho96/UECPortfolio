#pragma once

#include "CoreMinimal.h"
#include "Weapons/CSubAction.h"
#include "Weapons/CWeaponStructures.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CSubAction_Sword.generated.h"

UCLASS(Blueprintable)
class U2112_04_API UCSubAction_Sword : public UCSubAction
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Trace")
		float Distance = 1000;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
		float Speed = 200;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebug;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
		FDoActionData ActionData;

	UPROPERTY(EditDefaultsOnly, Category = "Actions")
		FHitData HitData;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Add-On")
		TSubclassOf<class ACGhostTrail> GhostTrailClass;

public:
	void Pressed() override;
	void Begin_SubAction_Implementation() override;
	void End_SubAction_Implementation() override;
	void Tick_Implementation(float InDeltaTime) override;

private:
	UFUNCTION()
		void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class UShapeComponent* InCollision, class ACharacter* InOther);

private:
	bool bMoving;

	FVector Start;
	FVector End;

private:
	TArray<class ACharacter*> Overlapped;

private:
	class ACGhostTrail* GhostTrail;
};