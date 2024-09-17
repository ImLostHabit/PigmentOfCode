

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseKart.h"
#include "GrabbableItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemReleasedDelegate, AGrabbableItem*, CurrentItem, bool, bWasSuccessful);




class UKartTrunk;
class ABaseKart;
class UBoxComponent;
class UStaticMeshComponent;

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
	virtual void ItemReleased(AGrabbableItem* ItemInput, bool bWasSuccessful);

	UFUNCTION()
	virtual void CheckForCollision(AGrabbableItem* ItemInput);
	

	
	UPROPERTY()
	AGrabbableItem* CurrentItem;

	UPROPERTY()
	ABaseKart* CurrentKart;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY()
	FItemReleasedDelegate ItemReleasedDelegate;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;





public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
