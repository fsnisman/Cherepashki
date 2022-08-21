/* Class Player character */

#pragma once

#include "SpawnButton.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UInputComponent;
class UCapsuleComponent;
class UCameraComponent;

UCLASS()
class MISSION_2_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	//////////////////////////
	//// Components

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;

protected:

	//////////////////////////
	//// Functions

	/* Initalize */
	APlayerCharacter();

	/* Move forward character */
	void MoveForward(float AxisValue);
	/* Move right character */
	void MoveRight (float AxisValue);
	/* Pressed F*/
	void PressedInteractive();

	/* Begin play */
	virtual void BeginPlay() override;
	/* Input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	ASpawnButton* SpawnButton;
};
