

#include "GrabbableItem.h"
#include "Grabber.h"
#include "Components/BoxComponent.h"
#include "BaseKart.h"
#include "TrunkCollision.h"

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
	ItemGrabbed.AddDynamic(this, &AGrabbableItem::OnItemGrabbed);
	GrabberReleased.AddDynamic(this, &AGrabbableItem::OnItemReleased);

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
		UE_LOG(LogTemp, Warning, TEXT("ITEM RELEASED.. \n Calling CheckForCollision.."));
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
		ItemState = EItemState::EIS_Single;
		UE_LOG(LogTemp, Warning, TEXT("Current Item Valid, checking CurrentBox"));
		UTrunkCollision* CurrentBox = CurrentKart->GetComponentByClass<UTrunkCollision>();
		if (CurrentBox)
		{
			
			UE_LOG(LogTemp, Warning, TEXT("CurrentItem & Box valid"));
			FHitResult SweepResult;
			UE_LOG(LogTemp, Warning, TEXT("CHECK FOR COL. OverlappedBox = %s"), *CurrentBox->GetName());
			BoxComponent->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECR_Ignore);
			CurrentKart->TrunkOverlapped.Broadcast(CurrentBox, this, BoxComponent, 0, false, SweepResult, true);
			bIsAttached = true;
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Item not released within bounds of trunk"));
		
		}
	}
}

void AGrabbableItem::ItemOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("ITEM ON OVERLAP TRIGGERED .. Overlapping item = %s"), *OtherComp->GetName());
	CurrentKart = Cast<ABaseKart>(OtherActor);
	if (OtherActor == CurrentKart)
	{
		UE_LOG(LogTemp, Warning, TEXT("SETTING ITEM STATE TO OVERLAP"));
		ItemState = EItemState::EIS_Overlapped;
	}
}

void AGrabbableItem::ItemOnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ItemState = EItemState::EIS_Single;
	
}

void AGrabbableItem::OnItemGrabbed(AGrabbableItem* TrunkItem, bool bWasSuccessful)
{
	bIsAttached = false;
	UE_LOG(LogTemp, Warning, TEXT("ITEM GRABBED VIA DELEGATE"));
	AGrabbableItem* CurrentTrunkItem;
	CurrentTrunkItem = Cast<AGrabbableItem>(TrunkItem);
	if (CurrentTrunkItem == TrunkItem)
	{
		if (CurrentTrunkItem->bIsAttached)
		{
			if (CurrentTrunkItem->GetAttachParentActor() != nullptr)
			{
			UE_LOG(LogTemp, Warning, TEXT("GRABBED TRUNK ITEM FOUND IN SLOT .. DETATCHING.."));
			CurrentTrunkItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			UE_LOG(LogTemp, Warning, TEXT("ITEM DETATCHED FROM SLOT .. SETTING STATE TO SINGLE.."));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("GRABBED TRUNK ITEM NOT FOUND IN SLOT.."));
			}
		}
		else if (!CurrentTrunkItem->bIsAttached)
		{
			UE_LOG(LogTemp, Warning, TEXT("ITEM NOT IN SLOT"));
			BoxComponent->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECR_Overlap);
			ItemState = EItemState::EIS_Single;
			UE_LOG(LogTemp, Warning, TEXT("ITEM SET TO SINGLE"));
		}

	}

}

void AGrabbableItem::OnItemReleased(bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("ON ITEM RELEASED DELEGATE ANSWERED"));
	if (bWasSuccessful)
	{
	ItemState = EItemState::EIS_Single;
	UE_LOG(LogTemp, Warning, TEXT("YOU NEEDED AN IF CHECK"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TRUNK ITEM LIKELY INVALID."));
	}
}


