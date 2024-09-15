

#include "GrabbableItem.h"
#include "Grabber.h"
#include "Components/BoxComponent.h"
#include "BaseKart.h"

// Sets default values
AGrabbableItem::AGrabbableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetVisibility(true);
	ItemMesh->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemBoxComponent"));
	BoxComponent->SetGenerateOverlapEvents(true);
	BoxComponent->SetupAttachment(ItemMesh);

}

// Called when the game starts or when spawned
void AGrabbableItem::BeginPlay()
{
	Super::BeginPlay();
	

}

void AGrabbableItem::ItemReleased()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Green, TEXT("YOU'RE SAFE .. FOR NOW."));
		UE_LOG(LogTemp, Warning, TEXT("Item Released, calling ItemReleasedDelegate..."));

		

	}
}

void AGrabbableItem::ItemGrabbed()
{
	UE_LOG(LogTemp, Warning, TEXT("ITEM GRABBED VIA DELEGATE"));


}

// Called every frame
void AGrabbableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

