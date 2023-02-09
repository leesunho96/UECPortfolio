#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Name.generated.h"

UCLASS()
class U2112_04_API UCUserWidget_Name : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateHealth(float InHealth, float InMaxHealth);

public:
	UFUNCTION(BlueprintImplementableEvent)
		void SetNameText(const FString& InName);

	UFUNCTION(BlueprintImplementableEvent)
		void SetControllerNameText(const FString& InName);
};
