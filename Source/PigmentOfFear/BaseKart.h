

#pragma once


#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "BaseKart.generated.h"



class UBoxComponent;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class ATrunkItem;
class USceneComponent;


// THIS IS WHERE YOU LEFT OFF
// RELATED DELEGATES NEED THE INPUT PARAMETERS OF ONCOMPONENTBEGINOVERLAP. THATS LIKELY WHY WE ARE UNABLE TO COMPILE.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FTrunkOverlapped, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult&, SweepResult, bool, bWasSuccessful);
//(FTrunkOverlapped, bool, bWasSuccessful);

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
	void CheckForCollision(ATrunkItem* TrunkItem);

	UPROPERTY()
	ABaseKart* CollidingKart;

	UFUNCTION(BlueprintCallable)
	void OnKartTrunkOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void AttachMeshToSocket(ATrunkItem* CurrentTrunkItem, const FName& InSocketName);

	UFUNCTION(BlueprintCallable)
	void OnKartTrunkEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* KartTrunkCollision01;

	UPROPERTY(EditAnywhere)
	UBoxComponent* KartTrunkCollision02;

	UPROPERTY(EditAnywhere)
	UBoxComponent* SlotCollision01;

	UPROPERTY(EditAnywhere)
	UBoxComponent* SlotCollision02;

	UPROPERTY(EditAnywhere)
	USceneComponent* TrunkSlot01;

	UPROPERTY(EditAnywhere)
	USceneComponent* TrunkSlot02;

	UPROPERTY()
	ATrunkItem* TrunkItem;

	UPROPERTY()
	FTrunkOverlapped TrunkOverlapped;

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
