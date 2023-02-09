#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentCollision);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentOverlap, class ACharacter*, InAttacker, class UShapeComponent*, InCollision, class ACharacter*, InOther);

UCLASS()
class U2112_04_API ACAttachment : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* Root;

public:	
	ACAttachment();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintCallable, Category = "Attachment")
		void AttachTo(FName InSocketName);

	UFUNCTION(BlueprintCallable, Category = "Attachment")
		void AttachToCollision(class UShapeComponent* InComponent, FName InSocketName);

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnBeginEquip();

	UFUNCTION(BlueprintImplementableEvent)
		void OnUnequip();
	
public:
	void OnCollision();
	void OffCollision();

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FAttachmentOverlap OnAttachmentBeginOverlap;
	FAttachmentOverlap OnAttachmentEndOverlap;

	FAttachmentCollision OnAttachmentCollision;
	FAttachmentCollision OffAttachmentCollision;


protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

protected:
	TArray<class UShapeComponent*> Collisions;
};
