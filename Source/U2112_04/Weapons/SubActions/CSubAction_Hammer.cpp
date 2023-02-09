#include "Weapons/SubActions/CSubAction_Hammer.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CMoveComponent.h"
#include "Weapons/CAttachment.h"
#include "Weapons/CDoAction.h"
#include "Weapons/AddOns/CGhostTrail.h"
#include "Weapons/AddOns/CAura.h"

void UCSubAction_Hammer::Pressed()
{
	CheckFalse(State->IsIdleMode());
	CheckTrue(State->IsSubActionMode());

	Super::Pressed();


	State->SetActionMode();
	State->OnSubActionMode();

	GhostTrail = Begin_GhostTrail(GhostTrailClass);

	ActionData.DoAction(Owner);
}

void UCSubAction_Hammer::Begin_SubAction_Implementation()
{
	Super::Begin_SubAction_Implementation();

	CheckNull(AuraClass);

	FActorSpawnParameters params;
	params.Owner = Owner;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform transform;
	transform.SetLocation(Owner->GetActorLocation());
	transform.AddToTranslation(AuraLocation);
	transform.SetRotation(FQuat(Owner->GetActorRotation()));

	Owner->GetWorld()->SpawnActor<ACAura>(AuraClass, transform, params);
}

void UCSubAction_Hammer::End_SubAction_Implementation()
{
	Super::End_SubAction_Implementation();

	State->SetIdleMode();
	State->OffSubActionMode();

	Move->Move();
	Move->DisableFixedCamera();

	End_GhostTrail(GhostTrail);
}