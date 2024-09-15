

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseKart.h"
#include "GrabbableItem.generated.h"



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
	virtual void ItemReleased();

	


	UPROPERTY()
	ABaseKart* CurrentKart;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ItemMesh;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;





public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
