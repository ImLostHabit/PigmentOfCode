

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabbableItem.h"
#include "Grabber.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIGMENTOFFEAR_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();


protected:

	

private:


	
	UPROPERTY()
	AGrabbableItem* GrabbedItem;

	// Grabber Properties

	UPROPERTY(EditAnywhere, Category = "Grabber")
	float MaxGrabDistance = 400.f;

	UPROPERTY(EditAnywhere, Category = "Grabber")
	float GrabRadius = 100;
	
	// How far the item grabbed is from the player once held.
	UPROPERTY(EditAnywhere, Category = "Grabber")
	float HoldDistance = 50.f;

	UFUNCTION()
	UPhysicsHandleComponent* GetPhysicsHandle() const;

	UFUNCTION()
	bool GetGrabbableInReach(FHitResult& OutHitResult) const;

		
};
