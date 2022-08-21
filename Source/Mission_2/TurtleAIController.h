/* Class AI Controller Turtle Pawn */

#pragma once

#include "TurtlePawn.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "TurtleAIController.generated.h"

UCLASS()
class MISSION_2_API ATurtleAIController : public AAIController
{
	GENERATED_BODY()

protected:

	//////////////////////////
	//// Variables

	/* Example class Pawn */
	UPROPERTY()
	ATurtlePawn* TurtlePawn;
	
	/* Array Travel Point */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Points", Meta = (MakeEditWidget = true))
	TArray<FVector> Points;
	/* Movement Accuracy Turtle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurancy")
	float MovementAccuracy = 0.0f;
	/* Reaction on Point*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingRange = 1000;
	/* Speed Reaction on next Point*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingSpeed = 0.1f;

	/* Count Travel Point */
	int32 CurrentPatrolPointIndex = INDEX_NONE;
	/* Timer */
	FTimerHandle TimerHandle;

protected:

	//////////////////////////
	//// Functions

	/* Begin Play */
	virtual void BeginPlay() override;

	/* Tick */
	virtual void Tick(float DeltaTime) override;

	/* Initalize pawn and travel points */
	void Initalize();

	/* Get value rotation on next Point*/
	float GetRotationValue();
};
