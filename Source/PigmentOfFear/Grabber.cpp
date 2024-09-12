


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

	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	


}

void UGrabber::Grab()
{

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle == nullptr)
	{
		return;
	}

	FVector StartLocation = GetComponentLocation();
	FVector EndLocation = StartLocation + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false);
	DrawDebugSphere(GetWorld(), EndLocation, 10, 10, FColor::Blue, false, 5);

	// Creating the sphere based on GrabRadius variable
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);


	FHitResult HitResult;

	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel2, Sphere);

	if (HasHit)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(HitResult.GetComponent(), 
			NAME_None, 
			HitResult.ImpactPoint, 
			GetComponentRotation()
		);
	}
	

	

}

void UGrabber::Release()
{
	


}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result =  GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber missing physics handle!"));
	}
	return Result;
	
}

