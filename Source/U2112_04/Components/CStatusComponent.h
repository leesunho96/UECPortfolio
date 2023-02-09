#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

UCLASS( ClassGroup=(Custom) )
class U2112_04_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealth = 100;

public:
	FORCEINLINE float GetHealth() { return Health; }
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }

public:	
	UCStatusComponent();

public:
	void Damage(float InAmount);

protected:
	virtual void BeginPlay() override;

private:
	class ACharacter* OwnerCharacter;

private:
	float Health;
};
