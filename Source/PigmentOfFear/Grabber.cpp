


#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	OnItemGrabbed.AddDynamic(this, &UGrabber::OnGrabbed);
	OnItemReleased.AddDynamic(this, &UGrabber::OnReleased);


	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabber::Grab()
{

	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Physics Handle Not Found"));
		return;
	}

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);

	if (HasHit)
	{
		AGrabbableItem* HitItem = Cast<AGrabbableItem>(HitResult.GetActor());
		if (HitItem)
		{
			if (GrabbedItem == nullptr)
			{
				// As long as we dont have a item already held, asign the HitItem as our GrabbedItem
				//GrabbedItem is a variable made in .h, 
			GrabbedItem = HitItem;
			OnItemGrabbed.Broadcast(true);
			}
		}
		// Crypt Raider 97

		AActor* HitActor = HitResult.GetActor();
		UE_LOG(LogTemp, Display, TEXT("Hit Actor"));

		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		HitResult.GetActor()->Tags.Add("Grabbed");

		PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, 
			NAME_None, 
			HitResult.ImpactPoint, 
			GetComponentRotation());
	
		

	}
	else
	{
		OnItemGrabbed.Broadcast(false);
	}
}

void UGrabber::OnGrabbed(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Error, TEXT("ON GRABBED SUCCESSFUL"));
		GrabbedItem->ItemGrabbed();
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GrabbedItem is nullptr"));
	}
}

void UGrabber::OnReleased(bool bWasSuccessful)
{

	if (bWasSuccessful)
	{
		GrabbedItem->ItemReleased();
		GrabbedItem = nullptr;
	}
	else
	{

	}

}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		OnItemReleased.Broadcast(true);
		PhysicsHandle->ReleaseComponent();
	}

}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* PhysicsHandle =  GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber missing physics handle!"));
	}

	return PhysicsHandle;
	
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{

	FVector StartLocation = GetComponentLocation();
	FVector EndLocation = StartLocation + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false);
	DrawDebugSphere(GetWorld(), EndLocation, 10, 10, FColor::Blue, false, 5);

	// Creating the sphere based on GrabRadius variable
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	return GetWorld()->SweepSingleByChannel(OutHitResult, StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel2, Sphere);

}



