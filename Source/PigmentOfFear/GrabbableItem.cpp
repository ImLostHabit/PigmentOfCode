

#include "Grabber.h"
#include "GrabbableItem.h"
#include "KartTrunk.h"

// Sets default values
AGrabbableItem::AGrabbableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrabbableItem::BeginPlay()
{
	Super::BeginPlay();
	
	ItemReleasedDelegate.AddDynamic(this, &AGrabbableItem::CallForCollision);

}

void AGrabbableItem::ItemReleased()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Green, TEXT("YOU'RE SAFE .. FOR NOW."));
		UE_LOG(LogTemp, Warning, TEXT("Item Released, calling ItemReleasedDelegate..."));
		ItemReleasedDelegate.Broadcast(true, CollidingKart);
	}
}

void AGrabbableItem::CallForCollision(bool bWasSuccesful, ABaseKart* CurrentKart)
{
	UE_LOG(LogTemp, Warning, TEXT("CallForCollision Answered for ItemReleasedDelegate, CastChecking CollidingKart..."));
	CollidingKart = Cast<ABaseKart>(CurrentKart);
	

	
	if (CurrentKart)
	{
		UE_LOG(LogTemp, Warning, TEXT("Colliding cart found. \n Calling CheckForCollision"));
		CurrentKart->CheckForCollision();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Colliding Kart Found"));
		return;
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

