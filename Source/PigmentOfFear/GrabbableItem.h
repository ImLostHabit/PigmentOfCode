

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrabbableItem.generated.h"

class UKartTrunk;

UCLASS()
class PIGMENTOFFEAR_API AGrabbableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrabbableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UKartTrunk* KartTrunk;

	void ItemReleased();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
