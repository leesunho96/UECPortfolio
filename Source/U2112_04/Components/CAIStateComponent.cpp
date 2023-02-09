#include "Components/CAIStateComponent.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UCAIStateComponent::UCAIStateComponent()
{

}

void UCAIStateComponent::BeginPlay()
{
	Super::BeginPlay();

}

EAIStateType UCAIStateComponent::GetType()
{
	return (EAIStateType)Blackboard->GetValueAsEnum(AIStateTypeKey);
}

bool UCAIStateComponent::IsWaitMode()
{
	return GetType() == EAIStateType::Wait;
}

bool UCAIStateComponent::IsApproachMode()
{
	return GetType() == EAIStateType::Approach;
}

bool UCAIStateComponent::IsActionMode()
{
	return GetType() == EAIStateType::Action;
}

bool UCAIStateComponent::IsPatrolMode()
{
	return GetType() == EAIStateType::Patrol;
}

bool UCAIStateComponent::IsHittedMode()
{
	return GetType() == EAIStateType::Hitted;
}

bool UCAIStateComponent::IsAvoidMode()
{
	return GetType() == EAIStateType::Avoid;
}

bool UCAIStateComponent::IsDeadMode()
{
	return GetType() == EAIStateType::Dead;
}

void UCAIStateComponent::SetWaitMode()
{
	ChangeType(EAIStateType::Wait);
}

void UCAIStateComponent::SetApproachMode()
{
	ChangeType(EAIStateType::Approach);
}

void UCAIStateComponent::SetActionMode()
{
	ChangeType(EAIStateType::Action);
}

void UCAIStateComponent::SetPatrolMode()
{
	ChangeType(EAIStateType::Patrol);
}

void UCAIStateComponent::SetHittedMode()
{
	ChangeType(EAIStateType::Hitted);
}

void UCAIStateComponent::SetAvoidMode()
{
	ChangeType(EAIStateType::Avoid);
}

void UCAIStateComponent::SetDeadMode()
{
	ChangeType(EAIStateType::Dead);
}

void UCAIStateComponent::ChangeType(EAIStateType InType)
{
	EAIStateType prevType = GetType();
	
	Blackboard->SetValueAsEnum(AIStateTypeKey, (uint8)InType);

	if (OnAIStateTypeChanged.IsBound())
		OnAIStateTypeChanged.Broadcast(prevType, InType);
}

ACPlayer* UCAIStateComponent::GetTargetPlayer()
{
	return Cast<ACPlayer>(Blackboard->GetValueAsObject(PlayerKey));
}

FVector UCAIStateComponent::GetLocation()
{
	return Blackboard->GetValueAsVector(LocationKey);
}