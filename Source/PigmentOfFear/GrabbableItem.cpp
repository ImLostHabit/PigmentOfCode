

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

	// ItemReleasedDelegate.AddDynamic(this, &AGrabbableItem::ItemReleased);
	//BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGrabbableItem::ItemReleased);
	//GrabberReleased.AddDynamic(this, &AGrabbableItem::ItemReleased);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGrabbableItem::ItemOnOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AGrabbableItem::ItemOnEndOverlap);


	
	

}

void AGrabbableItem::ItemReleased(bool bWasSuccessful)
{
	if (ItemState == EItemState::EIS_Overlapped)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITEM RELEASED WITHIN BOUNDS.. \n Calling CheckForCollision.."));
		CheckForCollision(true);
	}
	
	if(ItemState == EItemState::EIS_Single)
	{
		ItemState = EItemState::EIS_Single;
		UE_LOG(LogTemp, Warning, TEXT("ITEM RELEASED OUT OF BOUNDS"));
	}
	
}


void AGrabbableItem::CheckForCollision(bool ItemReleased)
{
	UE_LOG(LogTemp, Warning, TEXT("CheckForCollision answered"));

	
	if (ItemState == EItemState::EIS_Overlapped)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Item Valid, checking CurrentBox"));
		UBoxComponent* CurrentBox = CurrentKart->GetComponentByClass<UBoxComponent>();
		if (CurrentBox)
		{
			UE_LOG(LogTemp, Warning, TEXT("CurrentItem & Box valid, GO TO FUCKING BED"));

			FHitResult SweepResult;
			UBoxComponent* OverlappedComponent = CurrentKart->GetComponentByClass<UBoxComponent>();
			CurrentKart->TrunkOverlapped.Broadcast(OverlappedComponent, this, BoxComponent, 0, false, SweepResult, true);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Item not released within bounds"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Item not valid"));
	}
}

void AGrabbableItem::ItemOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("ITEM ON OVERLAP TRIGGERED .. CASTING TO CURRENT CART"));
	CurrentKart = Cast<ABaseKart>(OtherActor);
	UBoxComponent* KartCollision;
	KartCollision = CurrentKart->GetComponentByClass<UBoxComponent>();

	if (OtherActor == CurrentKart)
	{
	ItemState = EItemState::EIS_Overlapped;

	}

}

void AGrabbableItem::ItemOnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == CurrentKart)
	{
	ItemState = EItemState::EIS_Single;
	UE_LOG(LogTemp, Warning, TEXT("ITEM END OVERLAP TRIGGERED .. CASTING TO CURRENT CART"));
	CurrentKart = Cast<ABaseKart>(OtherActor);
	UBoxComponent* KartCollision;
	KartCollision = CurrentKart->GetComponentByClass<UBoxComponent>();
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

