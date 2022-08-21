#include "TurtlePawn.h"

#include "Kismet/GameplayStatics.h"

/* Initial */
ATurtlePawn::ATurtlePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Body Mesh
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	RootComponent = BodyMesh;

	// Hit Collider
	HitCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hit Collider"));
	HitCollider->SetupAttachment(BodyMesh);

	// Arrow Direction
	ArrowDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowDirection->SetupAttachment(BodyMesh);

	// Arrow Crown
	ArrowCrown = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Crown"));
	ArrowCrown->SetupAttachment(BodyMesh);

	// Audio
	AudioMovement = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Movement"));
	AudioMovement->SetupAttachment(BodyMesh);
}

/* Begin play */
void ATurtlePawn::BeginPlay()
{
	Super::BeginPlay();

	TargetForwardAxisValue = 0;

	// Check tag pawn
	if (this->ActorHasTag("Two"))
	{
		// Start timer stop move 0.5 sec
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurtlePawn::MoveForwardTwoTurtle, 1, true, 1);
	}

	// Check tag pawn
	if (this->ActorHasTag("Three"))
	{
		// Start timer back move 0.5 sec
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurtlePawn::MoveForwardThreeTurtle, 1, true, 1);
	}

	AudioMovement->Play();
}

/* Tick */
void ATurtlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check bool stop move
	if(!bStopMove)
	{
		// Location

		// Interp current forward value
		CurrentForwardAxisValue = FMath::FInterpTo(CurrentForwardAxisValue, TargetForwardAxisValue, DeltaTime, ForwardSmootheness);
		// Assign current to initial forward
		TargetForwardAxisValue = CurrentForwardAxisValue;
		// Get Current location pawn
		FVector CurrentLocation = GetActorLocation();
		// Get forward vector pawn
		FVector ForwardVector = GetActorForwardVector();
		// Vector move position
		FVector MovePosition = (CurrentLocation + ForwardVector * TargetMoveSpeed * TargetForwardAxisValue * DeltaTime);
		// New set location pawn
		SetActorLocation(MovePosition, true);

		// Rotation

		// Get current rotation pawn
		FRotator CurrentRotation = GetActorRotation();
		// Calculate rotation value
		float YawRotation = RotationSpeed * TargetRightAxisValue * DeltaTime;
		// Sum new rotation value with current
		YawRotation += CurrentRotation.Yaw;
		// New rotation pawn
		FRotator NewRotation = FRotator(0.f, YawRotation, 0.f);
		// New set rotation pawn
		SetActorRotation(NewRotation);
	}
}

/*  Value forward */
float ATurtlePawn::FMovementComponent(float ValueAxis)
{
	return TargetForwardAxisValue = ValueAxis;
}

/*  Value right */
float ATurtlePawn::FRotationComponent(float ValueAxis)
{
	return TargetRightAxisValue = ValueAxis;
}

/* Value movement two turtle */
void ATurtlePawn::MoveForwardTwoTurtle()
{
	// Stop move
	TargetMoveSpeed = 0;
	// Start timer normal move 1 sec
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurtlePawn::SetMoveSpeed, 1, true, 0.5);
}

/* Value movement three turtle */
void ATurtlePawn::MoveForwardThreeTurtle()
{
	// Back move
	TargetMoveSpeed = -TargetMoveSpeed;
	// Start timer normal move 1 sec
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurtlePawn::SetMoveSpeed, 1, true, 0.5);
}

/* Backup move speed */
void ATurtlePawn::SetMoveSpeed()
{
	TargetMoveSpeed = MoveSpeed * 2;

	// Check tag pawn
	if (this->ActorHasTag("Two"))
	{
		// Start timer stop move 0.5 sec
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurtlePawn::MoveForwardTwoTurtle, 1, true, 1);
	}

	// Check tag pawn
	if (this->ActorHasTag("Three"))
	{
		// Start timer back move 0.5 sec
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurtlePawn::MoveForwardThreeTurtle, 1, true, 1);
	}
}

void ATurtlePawn::Finish()
{
	AudioMovement->Stop();

	// Spawn particle 
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleFinish, GetActorTransform());
	// Spawn audio
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioFinish, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioFirework, GetActorLocation());

	// Spawn pawn
	FTransform SpawnTransform(ArrowCrown->GetComponentRotation(), ArrowCrown->GetComponentLocation(), FVector(1));
	ACrown* NewPawn = GetWorld()->SpawnActorDeferred<ACrown>(CrownClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	NewPawn->SetActorScale3D(FVector(0.05f, 0.05f, 0.05f));

	// Finish
	UGameplayStatics::FinishSpawningActor(NewPawn, SpawnTransform);
}

/* Get points travel */
TArray<FVector> ATurtlePawn::GetPoints()
{
	// Array Points
	TArray<FVector> ArrayPoints;

	// Add point in array
	for (const ATargetPoint* Point : Points)
	{
		ArrayPoints.Add(Point->GetActorLocation());
	}

	return ArrayPoints;
}

/* Set points */
void ATurtlePawn::SetPoints(const TArray<ATargetPoint*>& NewPatrollingPoints)
{
	Points = NewPatrollingPoints;
}

