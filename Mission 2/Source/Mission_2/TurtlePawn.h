/* Class Turtle Pawn */

#pragma once

#include "Crown.h"

#include "Engine/TargetPoint.h"
#include "Components/StaticMeshComponent.h"
#include <Components/SkeletalMeshComponent.h>
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include <Particles/ParticleSystem.h>

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TurtlePawn.generated.h"


class UStaticMeshComponent;
class UNiagaraSystem;
class UCapsuleComponent;
class UArrowComponent;

UCLASS()
class MISSION_2_API ATurtlePawn : public APawn
{
	GENERATED_BODY()

protected:

	//////////////////////////
	//// Components

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCapsuleComponent* HitCollider;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* ArrowDirection;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* ArrowCrown;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystem* ParticleFinish;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UAudioComponent* AudioMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USoundBase* AudioFinish;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USoundBase* AudioFirework;
	
	//////////////////////////
	//// Variables

	/* Array pawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn params")
	TSubclassOf<ACrown> CrownClass;

	/* Movement */

	/* Speed movement */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveSpeed = 100.f;
	/* Speed rotation */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float RotationSpeed = 100.f;
	/* Forward Smootheness */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float ForwardSmootheness = 0.1f;
	/* Rotation Smootheness */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float RotationSmootheness = 0.1f;

	/* AI param */

	/* Array travel points */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points", Meta = (MakeEditWidget = true))
	TArray<ATargetPoint*> Points;
	/* Accuracy movement */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurancy")
	float MovementAccuracy = 100;

	/* Timer */

	/* Timer movement */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timer movement")
	float TimerMovement = 1;
	/* Timer */
	FTimerHandle TimerHandle; //Timer

protected:

	//////////////////////////
	//// Functions

	/* Initalize */
	ATurtlePawn();

	/* Begin play */
	virtual void BeginPlay() override;
	/* Tick */
	virtual void Tick(float DeltaTime) override;

public:

	//////////////////////////
	//// Functions

	/* Get accuracy movement */
	UFUNCTION()
	float GetMovementAccuracy()
	{
		return MovementAccuracy;
	};

	/* Get points travel */
	UFUNCTION()
	TArray<FVector> GetPoints();

	/* Set points */ 
	UFUNCTION()
	void SetPoints(const TArray <ATargetPoint*>& NewPatrollingPoints);

	/* Finish */
	UFUNCTION(BlueprintCallable)
	void Finish();

	/* Value movement two turtle */
	void MoveForwardTwoTurtle();
	/* Value movement three turtle */
	void MoveForwardThreeTurtle();
	/* Backup move speed */
	void SetMoveSpeed();

	/* Value forward */
	float FMovementComponent(float ValueAxis);
	/* Value right */
	float FRotationComponent(float ValueAxis);

	//////////////////////////
	//// Variables

	/* Value forward */
	float TargetForwardAxisValue = 0.f;
	/* Value right */
	float TargetRightAxisValue = 0.f;
	/* Value current forward */
	float CurrentForwardAxisValue = 0.f;
	/* Value current right */
	float CurrentRightAxisValue = 0.f;
	/* Value move speed */
	float TargetMoveSpeed = MoveSpeed;
	/* Value bool stop move */
	bool bStopMove = false;
	/* Value bool stop move */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Finish")
	bool bFinish = false;
};
