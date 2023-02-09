#include "Weapons/CSubAction.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CMoveComponent.h"
#include "Components/CapsuleComponent.h"
#include "Weapons/AddOns/CGhostTrail.h"

UCSubAction::UCSubAction()
{

}

void UCSubAction::BeginPlay(ACharacter* InOwner,  ACAttachment* InAttachment,  UCDoAction* InDoAction)
{
	Owner = InOwner;
	Attachment = InAttachment;
	DoAction = InDoAction;

	State = CHelpers::GetComponent<UCStateComponent>(Owner);
	Move = CHelpers::GetComponent<UCMoveComponent>(Owner);
}

ACGhostTrail* UCSubAction::Begin_GhostTrail(TSubclassOf<ACGhostTrail>& InClass)
{
	CheckNullResult(InClass, nullptr);

	FActorSpawnParameters params;
	params.Owner = Owner;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector vector = Owner->GetActorLocation();
	vector.Z -= Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();


	FTransform transform;
	transform.SetTranslation(vector);

	return Owner->GetWorld()->SpawnActor<ACGhostTrail>(InClass, transform, params);
}

void UCSubAction::End_GhostTrail(ACGhostTrail* InDestroy)
{
	CheckNull(InDestroy);

	InDestroy->Destroy();
}