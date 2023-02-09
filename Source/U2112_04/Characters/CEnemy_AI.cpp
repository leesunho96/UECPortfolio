#include "Characters/CEnemy_AI.h"
#include "Global.h"
#include "Components/WidgetComponent.h"
#include "Components/CAIStateComponent.h"
#include "Widgets/CUserWidget_Name.h"

ACEnemy_AI::ACEnemy_AI()
{
	CHelpers::CreateActorComponent(this, &AIState, "AIState");
}

void ACEnemy_AI::BeginPlay()
{
	Super::BeginPlay();

	Cast<UCUserWidget_Name>(NameWidget->GetUserWidgetObject())->SetControllerNameText(GetController()->GetName());
}