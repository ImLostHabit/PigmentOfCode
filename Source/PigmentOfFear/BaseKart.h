

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
class UInteractWidget;
class UTrunkCollision;


	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FTrunkOverlapped, UTrunkCollision*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult&, SweepResult, bool, bWasSuccessful);
	

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
	void StoreInTrunk(UTrunkCollision* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void AttachMeshToSocket(ATrunkItem* CurrentTrunkItem, const FName& InSocketName);

	UFUNCTION(BlueprintCallable)
	void OnKartTrunkEndOverlap(UTrunkCollision* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable)
	void OnSeatEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable)
	void OnSeatOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

	//BLUEPRINT EVENTS
	UFUNCTION(BlueprintImplementableEvent)
	void ShowInteractPrompt();


	

	UPROPERTY(EditAnywhere)
	UTrunkCollision* KartTrunkCollision01;

	UPROPERTY(EditAnywhere)
	UTrunkCollision* KartTrunkCollision02;

	UPROPERTY(EditAnywhere)
	UBoxComponent* SeatCollision01;

	UPROPERTY(EditAnywhere)
	UBoxComponent* SeatCollision02;

	UPROPERTY(EditAnywhere)
	USceneComponent* TrunkSlot01;

	UPROPERTY(EditAnywhere)
	USceneComponent* TrunkSlot02;

	UPROPERTY()
	ATrunkItem* TrunkItem;

	UPROPERTY()
	FTrunkOverlapped TrunkOverlapped;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UInteractWidget> InteractionWidgetClass;

	UPROPERTY()
	UInteractWidget* CurrentInteractionWidget;

	


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
