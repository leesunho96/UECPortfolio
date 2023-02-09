#pragma once

#include "CoreMinimal.h"
#include "Weapons/CSubAction.h"
#include "CSubAction_Warp.generated.h"

UCLASS(Blueprintable)
class U2112_04_API UCSubAction_Warp : public UCSubAction
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		TSubclassOf<class ACameraActor> CameraActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		FVector CameraRelativeLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		TEnumAsByte<ECameraProjectionMode::Type> ProjectionMode;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		float OrthoWidth = 2000;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		float FieldOdView = 90;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		float BlendIn = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
		float BlendOut = 0;

public:
	UCSubAction_Warp();

public:
	virtual void Pressed() override;
	virtual void Released() override;

public:
	void BeginPlay(ACharacter* InOwner, ACAttachment* InAttachment, UCDoAction* InDoAction) override;

public:
	virtual void Tick_Implementation(float InDeltaTime) override;

private:
	class APlayerController* PlayerController;
	class ACameraActor* CameraActor;
};
