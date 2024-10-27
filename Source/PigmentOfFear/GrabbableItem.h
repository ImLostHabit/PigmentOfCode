

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseKart.h"
#include "GrabbableItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FItemReleasedDelegate, AGrabbableItem*, CurrentItem, ABaseKart*, KartInput, bool, bWasSuccessful);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGrabberReleased, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGrabbed, AGrabbableItem*, TrunkItem, bool, bWasSuccessful);





class UKartTrunk;
class ABaseKart;
class UBoxComponent;
class UStaticMeshComponent;
class UTrunkCollision;

UENUM(BlueprintType)
enum class EItemState : uint8
{

	EIS_Single UMETA(DisplayName = "Single"),
	EIS_Overlapped UMETA(DisplayName = "Overlapped"),
	EIS_Stored UMETA(DisplayName = "Stored")

};

UCLASS()
class PIGMENTOFFEAR_API AGrabbableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	
	EItemState ItemState = EItemState::EIS_Single;
	
	
	
	// Sets default values for this actor's properties
	AGrabbableItem();
	
	UFUNCTION()
	void OnItemGrabbed(AGrabbableItem* TrunkItem, bool bWasSuccessful);

	UFUNCTION()
	void OnItemReleased(bool bWasSuccessful);
	
	UFUNCTION()
	virtual void ItemReleased(bool bWasSuccessful);

	UFUNCTION()
	virtual void CheckForCollision(bool ItemReleased);

	

	UFUNCTION()
	void ItemOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ItemOnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



	UPROPERTY()
	bool bIsAttached = false;

	UPROPERTY()
	AGrabbableItem* CurrentItem;

	UPROPERTY()
	ABaseKart* CurrentKart;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY()
	FItemReleasedDelegate ItemReleasedDelegate;
	
	UPROPERTY()
	FGrabberReleased GrabberReleased;

	UPROPERTY()
	FOnGrabbed ItemGrabbed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;






public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
