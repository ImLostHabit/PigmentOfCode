

#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GrabbableItem.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BaseKart.h"

void ABaseKart::BeginPlay()
{
	Super::BeginPlay();
	
	KartTrunkCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseKart::OnKartTrunkOverlap);
}

void ABaseKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ABaseKart::Throttle);


	}


}

ABaseKart::ABaseKart()
{
	KartTrunkCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	KartTrunkCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	KartTrunkCollision->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);



}

void ABaseKart::OnKartTrunkOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("SOMETHING OVERLAPPED, VERIFYING IF GRABBABLE.."));

	if (OtherActor)
	{
		OverlappingItem = Cast<AGrabbableItem>(OtherActor);

		if (OverlappingItem)
		{
			UE_LOG(LogTemp, Warning, TEXT("OVERLAPPING ITEM VALID."));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("OVERLAPPING IS NOT VALID."));
		}

	}
}

void ABaseKart::CheckForCollision(AGrabbableItem* GrabbableItem)
{
	UE_LOG(LogTemp, Warning, TEXT("BASE KART CHECK FOR COLLISION ANSWERED"));




}

void ABaseKart::Throttle()
{

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Vroom."));
	}

}
