

#include "BaseKart.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GrabbableItem.h"
#include "Components/PrimitiveComponent.h"
#include "TrunkItem.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// GAMETRACE CHANNEL 1  = USABLE (HORROR ENGINE)
// GAMETRACE CHANNEL 2 = GRABBER
// GAMETRACE CHANNEL 3 = TRUNK COLLISION CHANNEL

void ABaseKart::BeginPlay()
{
	Super::BeginPlay();
	
	

	KartTrunkCollision01->OnComponentBeginOverlap.AddDynamic(this, &ABaseKart::OnKartTrunkOverlap);
	KartTrunkCollision01->OnComponentEndOverlap.AddDynamic(this, &ABaseKart::OnKartTrunkEndOverlap);
	KartTrunkCollision02->OnComponentBeginOverlap.AddDynamic(this, &ABaseKart::OnKartTrunkOverlap);
	KartTrunkCollision02->OnComponentEndOverlap.AddDynamic(this, &ABaseKart::OnKartTrunkEndOverlap);
	SlotCollision01->OnComponentBeginOverlap.AddDynamic(this, &ABaseKart::OnKartTrunkOverlap);
	SlotCollision02->OnComponentBeginOverlap.AddDynamic(this, &ABaseKart::OnKartTrunkOverlap);




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

	TrunkSlot01 = CreateDefaultSubobject<USceneComponent>(TEXT("TrunkSlot"));
	TrunkSlot01->SetupAttachment(RootComponent);
	TrunkSlot02 = CreateDefaultSubobject<USceneComponent>(TEXT("TrunkSlot02"));
	TrunkSlot02->SetupAttachment(RootComponent);
	SlotCollision01 = CreateDefaultSubobject<UBoxComponent>(TEXT("SlotCollision01"));
	SlotCollision02 = CreateDefaultSubobject<UBoxComponent>(TEXT("SlotCollision02"));
	SlotCollision01->SetupAttachment(TrunkSlot01);
	SlotCollision01->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECR_Block);
	SlotCollision02->SetupAttachment(TrunkSlot02);
	SlotCollision02->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECR_Block);


	KartTrunkCollision01 = CreateDefaultSubobject<UBoxComponent>(TEXT("TrunkCollision01"));
	KartTrunkCollision01->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	KartTrunkCollision01->SetupAttachment(RootComponent);
	KartTrunkCollision02 = CreateDefaultSubobject<UBoxComponent>(TEXT("TrunkCollision02"));
	KartTrunkCollision02->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	KartTrunkCollision02->SetupAttachment(RootComponent);

	SlotCollision01->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Overlap);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ABaseKart::OnKartTrunkOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("SOMETHING OVERLAPPED, VERIFYING IF GRABBABLE.."));


	TrunkItem = Cast<ATrunkItem>(OtherActor);

	if (OverlappedComponent == KartTrunkCollision01 && TrunkItem)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("TRUNK COLLISION 01 COLLIDED"));
			FAttachmentTransformRules TransformTules(EAttachmentRule::SnapToTarget, true);
			UE_LOG(LogTemp, Warning, TEXT("ATTACHING TO SLOT01 .."));
			OtherComp->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECR_Ignore);
			OtherComp->AttachToComponent(TrunkSlot01, TransformTules);
			

		}
	}


	if (OverlappedComponent == SlotCollision01 && TrunkItem)
	{
		if (GEngine)
		{

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("TRUNK COLLISION 01 COLLIDED"));
			FAttachmentTransformRules TransformTules(EAttachmentRule::SnapToTarget, true);
			UE_LOG(LogTemp, Warning, TEXT("ATTACHING TO SLOT01 .."));
			SlotCollision01->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECR_Ignore);
			UE_LOG(LogTemp, Warning, TEXT("TRUNK01 COLLISION SET TO IGNORE"));
			OtherComp->AttachToComponent(TrunkSlot01, TransformTules);
		}
	}


	if (OverlappedComponent == KartTrunkCollision02 && TrunkItem)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("TRUNK COLLISION 02 COLLIDED"));
			FAttachmentTransformRules TransformTules(EAttachmentRule::SnapToTarget, true);
			UE_LOG(LogTemp, Warning, TEXT("ATTACHING TO SLOT02 .."));
			SlotCollision02->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECR_Ignore);
			UE_LOG(LogTemp, Warning, TEXT("TRUNK02 COLLISION SET TO IGNORE"));
			OtherComp->AttachToComponent(TrunkSlot02, TransformTules);
		}
	}
}



void ABaseKart::CheckForCollision(ATrunkItem* OverlappingTrunkItem)
{
	UE_LOG(LogTemp, Warning, TEXT("BASE KART CHECK FOR COLLISION ANSWERED"));



}



void ABaseKart::OnKartTrunkEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("CART ENDED OVERLAP .. RE-ENABLING COLLISION"));
	OtherComp->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECR_Overlap);
	UE_LOG(LogTemp, Warning, TEXT("COLLISION RE-ENABLED"));
}

void ABaseKart::Throttle()
{

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Vroom."));
	}

}
