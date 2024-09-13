

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KartTrunk.generated.h"

UCLASS()
class PIGMENTOFFEAR_API AKartTrunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKartTrunk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
