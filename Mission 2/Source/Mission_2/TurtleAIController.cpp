#include "TurtleAIController.h"

/* Begin Play */
void ATurtleAIController::BeginPlay()
{
	Super::BeginPlay();
	Initalize();
}

/* Tick */
void ATurtleAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check Pawn in world
	if (!TurtlePawn)
	{
		// Initialize Pawn
		Initalize();
	}

	// Check Pawn in world
	if (!TurtlePawn)
	{
		return;
	}

	// Check on zero point
	if (CurrentPatrolPointIndex == INDEX_NONE)
	{
		// Stopped movement pawn
		TurtlePawn->bStopMove = true;

		if(!TurtlePawn->bFinish)
		{
			TurtlePawn->bFinish = true;
			TurtlePawn->Finish();
		}

		return;
	}

	// Movement pawn
	TurtlePawn->FMovementComponent(1.f);

	// Value rotation
	const float RotationValue = GetRotationValue();
	// Movement rotation pawn
	TurtlePawn->FRotationComponent(RotationValue);
}

/* Initalize pawn and travel points */
void ATurtleAIController::Initalize()
{
	// Cast on Pawn 
	TurtlePawn = Cast<ATurtlePawn>(GetPawn());

	// Check Pawn
	if (TurtlePawn)
	{
		// Get value movement accuracy 
		MovementAccuracy = TurtlePawn->GetMovementAccuracy();
		// Get Travel Points
		Points = TurtlePawn->GetPoints();
	}

	// Assign points to current value
	CurrentPatrolPointIndex = Points.Num() == 0 ? INDEX_NONE : 0;
}

/* Get value rotation on next Point */
float ATurtleAIController::GetRotationValue()
{
	// Current value points
	const FVector CurrentPoint = Points[CurrentPatrolPointIndex];
	// Current location pawn
	FVector PawnLocation = TurtlePawn->GetActorLocation();
	// Check distance between points
	if (FVector::Distance(CurrentPoint, PawnLocation) <= MovementAccuracy)
	{
		// Incrementation travel points
		CurrentPatrolPointIndex++;
		// Check on exceed the value
		if (CurrentPatrolPointIndex >= Points.Num())
		{
			CurrentPatrolPointIndex = INDEX_NONE;
		}
	}

	// Distance current point to pawn
	FVector MoveDirection = CurrentPoint - PawnLocation;
	// Normalize direction
	MoveDirection.Normalize();
	// Get forward vector pawn
	const FVector ForwardDirection = TurtlePawn->GetActorForwardVector();
	// Get right vector pawn
	const FVector RightDirection = TurtlePawn->GetActorRightVector();

	// Calculate forward angle
	const float ForwardAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(ForwardDirection, MoveDirection)));
	// Calculate right angle
	const float RightAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(RightDirection, MoveDirection)));

	// Value rotation
	float RotationValue = 0;

	// Check forward angle
	if (ForwardAngle > 5.f)
	{
		RotationValue = 1.f;
	}
	// Check right angle
	if (RightAngle > 90)
	{
		RotationValue = -RotationValue;
	}

	return RotationValue;
}