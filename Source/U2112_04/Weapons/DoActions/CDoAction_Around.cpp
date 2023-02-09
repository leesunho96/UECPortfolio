#include "Weapons/DoActions/CDoAction_Around.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Weapons/AddOns/CRotator_Object.h"

void UCDoAction_Around::DoAction()
{
	Super::DoAction();

	CheckFalse(DoActionDatas.Num() > 0);
	CheckFalse(State->IsIdleMode());

	DoActionDatas[0].DoAction(Owner);
}

void UCDoAction_Around::Begin_DoAction()
{
	Super::Begin_DoAction();
	CheckFalse(RotatorObjectClasses.Num() > 0);

	int32 index = UKismetMathLibrary::RandomIntegerInRange(0, RotatorObjectClasses.Num() - 1);


	FActorSpawnParameters params;
	params.Owner = Owner;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Owner->GetWorld()->SpawnActor<ACRotator_Object>(RotatorObjectClasses[index], params);
}

