#include "Notifies/CAnimNotifyState_CameraAnim.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Camera/CameraAnim.h"
#include "Characters/CPlayer.h"
#include "Weapons/AddOns/CCameraModifier.h"
#include "Kismet/KismetMathLibrary.h"

FString UCAnimNotifyState_CameraAnim::GetNotifyName_Implementation() const
{
	return "CameraAnim";
}

void UCAnimNotifyState_CameraAnim::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	CheckNull(CameraAnim);

	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	CheckNull(character);

	ACharacter* target = character;
	if (Target.IsNull() == false)
		target = Target.Get();


	APlayerController* controller = character->GetController<APlayerController>();
	CheckNull(controller);


	Modifier = Cast<UCCameraModifier>(controller->PlayerCameraManager->AddNewCameraModifier(UCCameraModifier::StaticClass()));

	float yaw = controller->GetControlRotation().Yaw;

	FVector location = target->GetActorLocation();
	location += FRotator(0, yaw, 0).RotateVector(LocationOffSet);

	Modifier->SetLocation(location);
	Modifier->SetRotation(FRotator(PitchOffSet, yaw,0));

	controller->SetControlRotation(FRotator(0, controller->GetControlRotation().Yaw, 0));;
	controller->PlayerCameraManager->PlayCameraAnim(CameraAnim, PlayRatio, 1, BlendInTime, BlendOutTime, false, false, 0, ECameraShakePlaySpace::UserDefined , controller->GetControlRotation());

}

void UCAnimNotifyState_CameraAnim::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	CheckNull(CameraAnim);

	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	CheckNull(character);

	APlayerController* controller = character->GetController<APlayerController>();
	CheckNull(controller);

	controller->PlayerCameraManager->RemoveCameraModifier(Modifier);
}
