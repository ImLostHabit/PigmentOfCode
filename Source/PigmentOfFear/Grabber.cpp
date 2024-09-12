


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

	// ...
	
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

	// Creating the sphere based on GrabRadius variable
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);


	FHitResult HitResult;

	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel2, Sphere);

	if (HasHit)
	{
		AActor* HitActor = HitResult.GetActor();
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
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, TEXT("Grabber Released"));
	}
}

