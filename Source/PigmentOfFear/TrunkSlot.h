

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TrunkSlot.generated.h"

class ABaseKart;
class UBoxComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIGMENTOFFEAR_API UTrunkSlot : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTrunkSlot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* TrunkSlot;

	UPROPERTY()
	ABaseKart* OwningKart;

	UPROPERTY(EditAnywhere)
	UBoxComponent* SlotCollision;
		
};
