#include "Characters/CEnemy.h"
#include "Global.h"
#include "CAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/CWeaponComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CMoveComponent.h"
#include "Weapons/CWeaponStructures.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/CUserWidget_Name.h"

ACEnemy::ACEnemy()
{
	CHelpers::CreateComponent<UWidgetComponent>(this, &NameWidget, "Name", GetMesh());

	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &Weapon, "Weapon");
	CHelpers::CreateActorComponent<UCMontagesComponent>(this, &Montages, "Montages");
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCMoveComponent>(this, &Move, "Move");


	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);

	TSubclassOf<UCAnimInstance> animInstance;
	CHelpers::GetClass<UCAnimInstance>(&animInstance, "AnimBlueprint'/Game/ABP_Character.ABP_Character_C'");
	GetMesh()->SetAnimClass(animInstance);

	GetCharacterMovement()->MaxWalkSpeed = 350;


	TSubclassOf<UCUserWidget_Name> nameClass;
	CHelpers::GetClass<UCUserWidget_Name>(&nameClass, "WidgetBlueprint'/Game/Widgets/WB_Name.WB_Name_C'");
	NameWidget->SetWidgetClass(nameClass);
	NameWidget->SetRelativeLocation(FVector(0, 0, 220));
	NameWidget->SetDrawSize(FVector2D(120, 20));
	NameWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	State->OnStateTypeChanged.AddDynamic(this, &ACEnemy::OnStateTypeChanged);

	for (int32 i = 0; i < GetMesh()->GetMaterials().Num(); i++)
	{
		UMaterialInstanceDynamic* instance = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterials()[i], this);
		GetMesh()->SetMaterial(i, instance);
	}

	ChangeColor(this, OriginColor);


	NameWidget->InitWidget();
	Cast<UCUserWidget_Name>(NameWidget->GetUserWidgetObject())->UpdateHealth(Status->GetHealth(), Status->GetMaxHealth());
	Cast<UCUserWidget_Name>(NameWidget->GetUserWidgetObject())->SetNameText(GetName());
	Cast<UCUserWidget_Name>(NameWidget->GetUserWidgetObject())->SetControllerNameText(GetController()->GetName());
}

float ACEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Damage.Amount = damage;
	Damage.Attacker = Cast<ACharacter>(EventInstigator->GetPawn());
	Damage.Event = (FHitDamageEvent *)&DamageEvent;

	State->SetHittedMode();

	return damage;
}

void ACEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
		case EStateType::Hitted: Hitted(); break;
		case EStateType::Dead: Dead(); break;
	}
}

void ACEnemy::Hitted()
{
	Status->Damage(Damage.Amount);
	Damage.Amount = 0;

	if (Status->GetHealth() <= 0.0f)
	{
		State->SetDeadMode();

		return;
	}


	ChangeColor(this, FLinearColor::Red);


	FTimerDelegate timerDelegate = FTimerDelegate::CreateUFunction(this, "RestoreColor");
	GetWorld()->GetTimerManager().SetTimer(RestoreColor_TimerHandle, timerDelegate, 0.2f, false);

	if (!!Damage.Event && !!Damage.Event->HitData)
	{
		FHitData* data = Damage.Event->HitData;

		data->PlayMontage(this);
		data->PlayHitStop(GetWorld());
		data->PlaySound(this);
		data->PlayEffect(GetWorld(), GetActorLocation());


		FVector start = GetActorLocation();
		FVector target = Damage.Attacker->GetActorLocation();
		FVector direction = target - start;
		direction.Normalize();

		LaunchCharacter(-direction * data->Launch, false, false);
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, target));
	}

	Damage.Attacker = nullptr;
	Damage.Event = nullptr;
}

void ACEnemy::RestoreColor()
{
	ChangeColor(this, OriginColor);
}

void ACEnemy::Dead()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Montages->PlayDeadMode();
}

void ACEnemy::End_Dead()
{
	Destroy();
}