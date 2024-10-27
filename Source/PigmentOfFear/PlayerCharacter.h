

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UUserWidget;
class UCapsuleComponent;
class USeatCollision;
class ABaseKart;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractButtonPressed, bool, bWasSuccessful);



enum class ECharacterState : uint8
{

	ECS_Single UMETA(DisplayName = "Single"),
	ECS_Overlapped UMETA(DisplayName = "Overlapped"),

};

UCLASS()
class PIGMENTOFFEAR_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	ECharacterState CharacterState = ECharacterState::ECS_Single;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* MovementContext;

	UPROPERTY(EditAnywhere)
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere)
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere)
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere)
	UInputAction* GrabAction;

	UPROPERTY(EditAnywhere)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY()
	USeatCollision* OverlappingSeat;

	UPROPERTY()
	ABaseKart* CurrentKart;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	FInteractButtonPressed InteractButtonPressed;
	
	UPROPERTY()
	UCapsuleComponent* CapsuleComp;



	UFUNCTION()
	void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	bool bIsPlayerOverlapped;


	

	
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Interact();

	void Grab();

	void Jump();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
