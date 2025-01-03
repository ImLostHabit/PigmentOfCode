
#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "BaseKart.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);


	

}



// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComp = GetCapsuleComponent();

	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnPlayerOverlap);
	CapsuleComp->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnPlayerEndOverlap);

	PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController == Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MovementContext, 0);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("THE PLAYER IS RECIEVING ITS INPUT PARAMS"));
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Grab);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

	}

}


void APlayerCharacter::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("THE PLAYER IS BEING NOTICED"));

	CurrentKart = Cast<ABaseKart>(OtherActor);
	if (OtherActor == CurrentKart)
	{
		
		CharacterState = ECharacterState::ECS_Overlapped;
		bIsPlayerOverlapped = true;
	}
}

void APlayerCharacter::OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	UE_LOG(LogTemp, Warning, TEXT("THE PLAYER IS WALKING AWAY"));

	CurrentKart = Cast<ABaseKart>(OtherActor);
	if (OtherActor == CurrentKart)
	{
		CharacterState = ECharacterState::ECS_Single;
		bIsPlayerOverlapped = false;
	}
}


void APlayerCharacter::Move(const FInputActionValue& Value)
{

	
	// We technically are only moving within 2 planes. X and Y, hence 2D Vector.
	const FVector2D MovementVector = Value.Get<FVector2D>();

	// Grabbing our rotation, then storing the YAW rotation in its own variable.
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
	 

}

void APlayerCharacter::Look(const FInputActionValue& Value)
{

	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerPitchInput(LookAxisValue.Y);
		AddControllerYawInput(LookAxisValue.X);
	}
}

void APlayerCharacter::Interact()
{

	if (bIsPlayerOverlapped)
	{
		UE_LOG(LogTemp, Warning, TEXT("*Enters Vehicle*"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("*Cries*"));
	}

	//if overlapping component = *some type of interactable*
	// call item interacted delegate
	// this way, anything interactable can have its own function. 
	// Start with the Kart, any other interactables should be "straightforward" once figuring the Kart out.
	
	
}	
	

void APlayerCharacter::Grab()
{


}

void APlayerCharacter::Jump()
{
}





