

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseKart.h"
#include "KartTrunk.h"
#include "GrabbableItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemReleasedDelegate, bool, bWasSuccessful, ABaseKart*, CurrentKart);

class UKartTrunk;

UCLASS()
class PIGMENTOFFEAR_API AGrabbableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrabbableItem();
	UFUNCTION()
	void ItemGrabbed();
	
	UFUNCTION()
	void ItemReleased();
	
	UFUNCTION()
	void CallForCollision(bool bWasSuccessful, ABaseKart* CurrentKart);

	//Delegates
	FItemReleasedDelegate ItemReleasedDelegate;

	UPROPERTY()
	UKartTrunk* KartTrunk;
	
	UPROPERTY()
	ABaseKart* CollidingKart;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
