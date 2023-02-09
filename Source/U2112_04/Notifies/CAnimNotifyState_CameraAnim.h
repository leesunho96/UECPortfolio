#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_CameraAnim.generated.h"

UCLASS()
class U2112_04_API UCAnimNotifyState_CameraAnim : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "CameraAnim")
		class UCameraAnim* CameraAnim;

	UPROPERTY(EditAnywhere, Category = "CameraAnim")
		float PlayRatio = 1;

	UPROPERTY(EditAnywhere, Category = "CameraAnim")
		float BlendInTime = 0;

	UPROPERTY(EditAnywhere, Category = "CameraAnim")
		float BlendOutTime = 0;

	UPROPERTY(EditAnywhere, Category = "CameraAnim")
		TSoftObjectPtr<class ACharacter> Target;

	UPROPERTY(EditAnywhere, Category = "Modifier")
		FVector LocationOffSet = FVector(-400, 0, 90);

	UPROPERTY(EditAnywhere, Category = "Modifier")
		float PitchOffSet = -15;

public:
	FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;

private:
	class UCCameraModifier* Modifier;

};
