

#pragma once


#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "BaseKart.generated.h"


class UBoxComponent;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class AGrabbableItem;

/**
 * 
 */
UCLASS()
class PIGMENTOFFEAR_API ABaseKart : public AWheeledVehiclePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	ABaseKart();

	UFUNCTION(BlueprintCallable)
	void CheckForCollision(AGrabbableItem* GrabbableItem);

	ABaseKart* CollidingKart;

	UFUNCTION()
	void OnKartTrunkOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* KartTrunkCollision;

	UPROPERTY()
	AGrabbableItem* OverlappingItem;

protected:




private:


	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* Look;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* ThrottleAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* Brake;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* HandBrake;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* Steer;


	// Kart movement functions

	UFUNCTION(BlueprintCallable)
	void Throttle();






	
};
