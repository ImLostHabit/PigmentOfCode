

#include "BaseKart.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GrabbableItem.h"
#include "TrunkItem.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidget.h"
#include "SeatCollision.h"
#include "TrunkCollision.h"

// GAMETRACE CHANNEL 1  = USABLE (HORROR ENGINE)
// GAMETRACE CHANNEL 2 = GRABBER
// GAMETRACE CHANNEL 3 = TRUNK COLLISION CHANNEL

void ABaseKart::BeginPlay()
{
	Super::BeginPlay();
	
	
	TrunkOverlapped.AddDynamic(this, &ABaseKart::StoreInTrunk);


	SeatCollision01->OnComponentBeginOverlap.AddDynamic(this, &ABaseKart::OnSeatOverlap);
	SeatCollision01->OnComponentEndOverlap.AddDynamic(this, &ABaseKart::OnSeatEndOverlap);
	SeatCollision02->OnComponentBeginOverlap.AddDynamic(this, &ABaseKart::OnSeatOverlap);
	SeatCollision02->OnComponentEndOverlap.AddDynamic(this, &ABaseKart::OnSeatEndOverlap);

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

	TrunkSlot01 = CreateDefaultSubobject<USceneComponent>(TEXT("TrunkSlot01"));
	TrunkSlot01->SetupAttachment(RootComponent);
	TrunkSlot02 = CreateDefaultSubobject<USceneComponent>(TEXT("TrunkSlot02"));
	TrunkSlot02->SetupAttachment(RootComponent);
	SeatCollision01 = CreateDefaultSubobject<USeatCollision>(TEXT("SeatCollision01"));
	SeatCollision02 = CreateDefaultSubobject<USeatCollision>(TEXT("SeatCollision02"));
	SeatCollision01->SetupAttachment(RootComponent);
	//SeatCollision01->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECR_Overlap);
	SeatCollision02->SetupAttachment(RootComponent);
	//SeatCollision02->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECR_Overlap);
	SeatCollision01->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SeatCollision02->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	

	KartTrunkCollision01 = CreateDefaultSubobject<UTrunkCollision>(TEXT("TrunkCollision01"));
	KartTrunkCollision01->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	KartTrunkCollision01->SetupAttachment(RootComponent);
	KartTrunkCollision02 = CreateDefaultSubobject<UTrunkCollision>(TEXT("TrunkCollision02"));
	KartTrunkCollision02->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	KartTrunkCollision02->SetupAttachment(RootComponent);


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ABaseKart::StoreInTrunk(UTrunkCollision* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("STORE IN TRUNK TRIGGERED"));

	// Validating our OtherActor with a variable
	TrunkItem = Cast<ATrunkItem>(OtherActor);
	UTrunkCollision* TrunkCollision = Cast<UTrunkCollision>(OverlappedComponent);

	if (TrunkItem)
	{
		// SEAT COLLISION RELATIONSHIP WITH PLAYER

		if (OverlappedComponent == KartTrunkCollision01)
		{
			AttachMeshToSocket(TrunkItem, FName("TrunkSlot01"));
			TrunkItem->bIsAttached = true;
			UE_LOG(LogTemp, Warning, TEXT("ATTACHING ITEM TO SLOT01 .. \n OverlappedComponeent = %s, OtherActor = %s"), *OverlappedComponent->GetName(), *OtherActor->GetName());

		}
		else if (OverlappedComponent == KartTrunkCollision02)
		{
			UE_LOG(LogTemp, Warning, TEXT("TRUNK 02 TRIGGERED, ATTACHING ITEM TO SLOT02 .."));
			FAttachmentTransformRules TransformTules(EAttachmentRule::SnapToTarget, true);
			UE_LOG(LogTemp, Warning, TEXT("ATTACHING TO SLOT02 .."));
			AttachMeshToSocket(TrunkItem, FName("TrunkSlot02"));
			TrunkItem->bIsAttached = true;

		}
	}
}



void ABaseKart::AttachMeshToSocket(ATrunkItem* CurrentTrunkItem, const FName& InSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	TrunkItem->AttachToComponent(TrunkSlot01, TransformRules, InSocketName);
	

}



void ABaseKart::OnKartTrunkEndOverlap(UTrunkCollision* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("CART ENDED OVERLAP .. RE-ENABLING COLLISION"));
	OtherComp->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECR_Overlap);
	UE_LOG(LogTemp, Warning, TEXT("COLLISION RE-ENABLED"));
}

void ABaseKart::OnSeatEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("SEAT IS GETTING COLD..."));
	

		
}

void ABaseKart::OnSeatOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("SEAT IS GETTING WARM..."));
	
}
void ABaseKart::Throttle()
{

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Vroom."));
	}

}


