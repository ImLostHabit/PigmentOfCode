

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


	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGrabbableItem::ItemOnOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AGrabbableItem::ItemOnEndOverlap);

	ItemState = EItemState::EIS_Single;

}

// Called every frame
void AGrabbableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrabbableItem::ItemReleased(bool bWasSuccessful)
{
	if (ItemState == EItemState::EIS_Overlapped)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITEM RELEASED WIT.. \n Calling CheckForCollision.."));
		CheckForCollision(true);
	}
	else
	{
	UE_LOG(LogTemp, Warning, TEXT("ITEM RELEASED OUT OF BOUNDS"));
	ItemState = EItemState::EIS_Single;
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
			UE_LOG(LogTemp, Warning, TEXT("CurrentItem & Box valid"));
			FHitResult SweepResult;
			UBoxComponent* OverlappedBox = CurrentKart->GetComponentByClass<UBoxComponent>();
			BoxComponent->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECR_Ignore);
			CurrentKart->TrunkOverlapped.Broadcast(OverlappedBox, this, BoxComponent, 0, false, SweepResult, true);
			UE_LOG(LogTemp, Warning, TEXT("SETTING ITEM TO SINGLE"));
			ItemState = EItemState::EIS_Single;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Item not released within bounds"));
			ItemState = EItemState::EIS_Single;
		}
	}
}

void AGrabbableItem::ItemOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("ITEM ON OVERLAP TRIGGERED .."));
	CurrentKart = Cast<ABaseKart>(OtherActor);
	if (OtherActor == CurrentKart)
	{
		UE_LOG(LogTemp, Warning, TEXT("SETTING ITEM STATE TO OVERLAP"));
		ItemState = EItemState::EIS_Overlapped;
	}
	UBoxComponent* KartCollision;
	KartCollision = CurrentKart->GetComponentByClass<UBoxComponent>();
}

void AGrabbableItem::ItemOnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("ITEM END OVERLAP TRIGGERED .. SETTING ITEM TO SINGLE"));
	ItemState = EItemState::EIS_Single;
}

void AGrabbableItem::ItemGrabbed()
{
	UE_LOG(LogTemp, Warning, TEXT("ITEM GRABBED VIA DELEGATE"));
}


