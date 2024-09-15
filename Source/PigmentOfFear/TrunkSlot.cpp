

#include "BaseKart.h"
#include "Components/BoxComponent.h"
#include "TrunkSlot.h"

// Sets default values for this component's properties
UTrunkSlot::UTrunkSlot()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;



	TrunkSlot = CreateDefaultSubobject<USceneComponent>(TEXT("Trunk Slot"));
	SlotCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SlotBox"));
	SlotCollision->SetupAttachment(TrunkSlot);

	OwningKart = Cast<ABaseKart>(TrunkSlot->GetOwner());
	if (OwningKart)
	{
		// Knowing we are in a SceneComponent, we have to create a RootComponent as a Scene
		// Component doesn't have one initially. 
		USceneComponent* RootComponent = OwningKart->GetRootComponent();
			if (RootComponent && TrunkSlot && SlotCollision)
			{
			//TrunkSlot->SetupAttachment(RootComponent);
			
			}
			else
			{
			UE_LOG(LogTemp, Error, TEXT("TRUNK SLOT LOST"));
			}

	}



}


// Called when the game starts
void UTrunkSlot::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTrunkSlot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

