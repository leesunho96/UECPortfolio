#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Characters/ICharacter.h"
#include "CEnemy.generated.h"

UCLASS()
class U2112_04_API ACEnemy 
	: public ACharacter
	, public IICharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Color")
		FLinearColor OriginColor = FLinearColor::White;

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* NameWidget;

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCWeaponComponent* Weapon;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMoveComponent* Move;

public:
	ACEnemy();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	UFUNCTION()
		void RestoreColor();

private:
	void Hitted();
	void Dead();

private:
	void End_Dead() override;

private:
	struct FDamageData
	{
		float Amount;
		class ACharacter* Attacker;
		struct FHitDamageEvent* Event;
	} Damage;

private:
	FTimerHandle RestoreColor_TimerHandle;
};
