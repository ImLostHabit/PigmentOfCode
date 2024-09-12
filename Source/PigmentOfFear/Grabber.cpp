


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

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

	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("FOUND PHYSICS HANDLE %s"), *PhysicsHandle->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO PHYSICS HANDLE FOUND"));
	}
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	


}

void UGrabber::Grab()
{

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
		AActor* HitActor = HitResult.GetActor();
		
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Emerald, false, 5);
		DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::White, false, 5);


		FString ActorName = HitActor->GetActorNameOrLabel();
		UE_LOG(LogTemp, Warning, TEXT("Actor %s Found!"), *ActorName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Actor Found!"));
	}

	

}

void UGrabber::Release()
{
	


}

