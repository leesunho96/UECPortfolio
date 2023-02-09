#include "Weapons/SubActions/CSubAction_Fist.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CMoveComponent.h"
#include "Weapons/CAttachment.h"
#include "Weapons/CDoAction.h"
#include "Weapons/AddOns/CGhostTrail.h"

void UCSubAction_Fist::Pressed()
{
	CheckFalse(State->IsIdleMode());
	CheckTrue(State->IsSubActionMode());

	Super::Pressed();


	State->SetActionMode();
	State->OnSubActionMode();

	GhostTrail = Begin_GhostTrail(GhostTrailClass);

	ActionData.DoAction(Owner);
}

void UCSubAction_Fist::Begin_SubAction_Implementation()
{
	Super::Begin_SubAction_Implementation();

	Attachment->OffAttachmentCollision.Remove(DoAction, "OffAttachmentCollision");
	Attachment->OnAttachmentBeginOverlap.Remove(DoAction, "OnAttachmentBeginOverlap");

	Attachment->OffAttachmentCollision.AddDynamic(this, &UCSubAction_Fist::OffAttachmentCollision);
	Attachment->OnAttachmentBeginOverlap.AddDynamic(this, &UCSubAction_Fist::OnAttachmentBeginOverlap);
}

void UCSubAction_Fist::End_SubAction_Implementation()
{
	Super::End_SubAction_Implementation();

	Attachment->OffAttachmentCollision.Remove(this, "OffAttachmentCollision");
	Attachment->OnAttachmentBeginOverlap.Remove(this, "OnAttachmentBeginOverlap");

	Attachment->OffAttachmentCollision.AddDynamic(DoAction, &UCDoAction::OffAttachmentCollision);
	Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &UCDoAction::OnAttachmentBeginOverlap);


	State->SetIdleMode();
	State->OffSubActionMode();

	Move->Move();
	Move->DisableFixedCamera();

	HitIndex = 0;


	End_GhostTrail(GhostTrail);
}

void UCSubAction_Fist::OffAttachmentCollision()
{
	Hitted.Empty();

	HitIndex++;
}

void UCSubAction_Fist::OnAttachmentBeginOverlap(ACharacter* InAttacker, UShapeComponent* InCollision, ACharacter* InOther)
{
	CheckNull(InOther);
	for (ACharacter* character : Hitted)
	{
		CheckTrue(character == InOther);
	}

	Hitted.AddUnique(InOther);

	CheckTrue(HitIndex >= HitDatas.Num());
	HitDatas[HitIndex].SendDamage(Owner, InOther);
}