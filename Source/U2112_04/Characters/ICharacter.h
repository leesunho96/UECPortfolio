#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacter.generated.h"

UINTERFACE(MinimalAPI)
class UICharacter : public UInterface
{
	GENERATED_BODY()
};

class U2112_04_API IICharacter
{
	GENERATED_BODY()

public:
	virtual void End_Dead() = 0;

	virtual void ChangeColor(class ACharacter* InCharacter, FLinearColor InColor);
};
