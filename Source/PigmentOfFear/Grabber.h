

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemGrabbed, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemReleased, bool, bWasSuccessful);


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

	void OnGrabbed(bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void Release();


	// Custom Delegates for the GrabbableItem to bind callbacks for
	FOnItemGrabbed OnItemGrabbed;
	FOnItemReleased OnItemReleased;


private:

	


	// Grabber Properties

	UPROPERTY(EditAnywhere, Category = "Grabber")
	float MaxGrabDistance = 400.f;

	UPROPERTY(EditAnywhere, Category = "Grabber")
	float GrabRadius = 100;
	
	// How far the item grabbed is from the player once held.
	UPROPERTY(EditAnywhere, Category = "Grabber")
	float HoldDistance = 50.f;

	UPhysicsHandleComponent* GetPhysicsHandle() const;

	bool GetGrabbableInReach(FHitResult& OutHitResult) const;

		
};
