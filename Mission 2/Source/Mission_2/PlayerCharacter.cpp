#include "PlayerCharacter.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

/* Initalize */
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());
}

/* Begin play */
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

/* Input */
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MouseTurn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MouseUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Interactive", IE_Released, this, &APlayerCharacter::PressedInteractive);
}

/* Move Forward character */
void APlayerCharacter::MoveForward(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), AxisValue);
	}
}

/* Move Right character */
void APlayerCharacter::MoveRight(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), AxisValue);
	}
}

/* Interactive */
void APlayerCharacter::PressedInteractive()
{
	// Line Trace
	FVector Start = Camera->GetComponentLocation();
	FVector End = (GetActorForwardVector() * 120.0f) + Start;
	FHitResult Hit;

	FCollisionQueryParams TraceParams;

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

	// Check line trace button
	if(Hit.bBlockingHit)
	{
		SpawnButton = Cast<ASpawnButton>(Hit.GetActor());
		SpawnButton->StartSpawn();
	}

}


