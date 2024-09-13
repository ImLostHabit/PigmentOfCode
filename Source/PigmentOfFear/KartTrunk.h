

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "KartTrunk.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIGMENTOFFEAR_API UKartTrunk : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKartTrunk();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



		
};