#include "Weapons/AddOns/CRotator_Object.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"

ACRotator_Object::ACRotator_Object()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UCapsuleComponent>(this, &Capsule, "Capsule");
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle", Capsule);

	InitialLifeSpan = 5;


	CHelpers::GetAsset<UAnimMontage>(&HitData.Montage, "AnimMontage'/Game/Character/Montages/Common/HitReaction_Montage.HitReaction_Montage'");
	
	HitData.Launch = 0;
	HitData.Power = 5;
}

void ACRotator_Object::BeginPlay()
{
	Super::BeginPlay();

	Angle = UKismetMathLibrary::RandomFloatInRange(0, 360);

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACRotator_Object::OnComponentBeginOverlap);
	Capsule->OnComponentEndOverlap.AddDynamic(this, &ACRotator_Object::OnComponentEndOverlap);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACRotator_Object::SendDamage, DamageInteval, true);
}

void ACRotator_Object::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void ACRotator_Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector location = GetOwner()->GetActorLocation();

	Angle += (bNegative ? -Speed : +Speed) * DeltaTime;
	if (FMath::IsNearlyEqual(Angle, bNegative ? -360 : +360))
		Angle = 0;


	FVector distance = FVector(Distance, 0, 0);
	FVector value = distance.RotateAngleAxis(Angle, FVector::UpVector);
	location += value;

	SetActorLocation(location);
	SetActorRotation(FRotator(0, Angle, 0));
}

void ACRotator_Object::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(GetOwner() == OtherActor);

	ACharacter* character = Cast<ACharacter>(OtherActor);
	if (!!character)
		Hitted.AddUnique(character);
}

void ACRotator_Object::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckTrue(GetOwner() == OtherActor);

	ACharacter* character = Cast<ACharacter>(OtherActor);
	if (!!character)
		Hitted.Remove(character);
}

void ACRotator_Object::SendDamage()
{
	for (int32 i = Hitted.Num() - 1; i >= 0; i--)
		HitData.SendDamage(Cast<ACharacter>(GetOwner()), Hitted[i]);
}