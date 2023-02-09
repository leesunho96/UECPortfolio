#include "Weapons/SubActions/CSubAction_Thorn.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Weapons/AddOns/CThornObject.h"

UCSubAction_Thorn::UCSubAction_Thorn()
{

}

void UCSubAction_Thorn::Pressed()
{
	CheckTrue(State->IsSubActionMode());

	Super::Pressed();

	State->OnSubActionMode();

	ActionData.DoAction(Owner);
}

void UCSubAction_Thorn::Begin_SubAction_Implementation()
{
	Super::Begin_SubAction_Implementation();

	CheckNull(ObjectClass);

	FActorSpawnParameters params;
	params.Owner = Owner;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform transform;

	FVector ownerLocation = Owner->GetActorLocation();
	ownerLocation += Owner->GetActorRotation().RotateVector(ObjectLocation);

	transform.SetLocation(ownerLocation);

	Owner->GetWorld()->SpawnActor<ACThornObject>(ObjectClass, transform, params);
}

void UCSubAction_Thorn::End_SubAction_Implementation()
{
	Super::End_SubAction_Implementation();

	State->OffSubActionMode();
	State->SetIdleMode();
}