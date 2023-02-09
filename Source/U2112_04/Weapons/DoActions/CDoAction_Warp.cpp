#include "Weapons/DoActions/CDoAction_Warp.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CAIStateComponent.h"
#include "Weapons/CAttachment.h"

void UCDoAction_Warp::BeginPlay(ACAttachment* InAttachment, UCEquipment* InEquipment, ACharacter* InOwner, const TArray<FDoActionData>& InDoActionDatas, const TArray<FHitData>& InHitDatas)
{
	Super::BeginPlay(InAttachment, InEquipment, InOwner, InDoActionDatas, InHitDatas);

	Decal = CHelpers::GetComponent<UDecalComponent>(InAttachment);
	PlayerController = Owner->GetController<APlayerController>();

	AIState = CHelpers::GetComponent<UCAIStateComponent>(InOwner);
}

void UCDoAction_Warp::DoAction()
{
	Super::DoAction();
	
	CheckFalse(DoActionDatas.Num() > 0);
	CheckFalse(State->IsIdleMode());
	

	FRotator rotation;
	if (GetCursorLocationAndRotation(MoveToLocation, rotation))
	{
		float height = Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		MoveToLocation = FVector(MoveToLocation.X, MoveToLocation.Y, MoveToLocation.Z + height);

		float yaw = UKismetMathLibrary::FindLookAtRotation(Owner->GetActorLocation(), MoveToLocation).Yaw;
		Owner->SetActorRotation(FRotator(0, yaw, 0));
	}

	DoActionDatas[0].DoAction(Owner);
}

void UCDoAction_Warp::Begin_DoAction()
{
	Super::Begin_DoAction();
	
	if (!!PlayerController)
	{
		Owner->SetActorLocation(MoveToLocation);

		return;
	}
	
	CheckNull(AIState);
	Owner->SetActorLocation(AIState->GetLocation());
}

void UCDoAction_Warp::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);

	FVector location = FVector::ZeroVector;
	FRotator rotation = FRotator::ZeroRotator;

	if (GetCursorLocationAndRotation(location, rotation) == false)
	{
		Decal->SetVisibility(false);

		return;
	}

	Decal->SetVisibility(true);

	if (bDoingAction == false)
	{
		Decal->SetWorldLocation(location);
		Decal->SetWorldRotation(rotation);
	}
}

bool UCDoAction_Warp::GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotation)
{
	CheckNullResult(PlayerController, false);


	FHitResult hitResult;
	PlayerController->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, hitResult);
	CheckFalseResult(hitResult.bBlockingHit, false);


	OutLocation = hitResult.Location;
	OutRotation = hitResult.ImpactNormal.Rotation();

	return true;
}