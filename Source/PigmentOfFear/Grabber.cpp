


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

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



