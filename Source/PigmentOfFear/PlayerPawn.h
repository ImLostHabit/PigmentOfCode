

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;
class UCapsuleComponent;

struct FInputActionValue;

UCLASS()
class PIGMENTOFFEAR_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

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

	UPROPERTY()
	USpringArmComponent* SpringArm;

	UPROPERTY()
	UCameraComponent* Camera;

	UPROPERTY()
	UCapsuleComponent* CapsuleComp;

	UPROPERTY()
	APlayerController* PlayerController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



protected:

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Interact();

	void Grab();

	void Jump();


};
