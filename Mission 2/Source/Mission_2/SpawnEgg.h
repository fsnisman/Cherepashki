/* Class spawn egg */

#pragma once

#include "TurtlePawn.h"
#include "Engine/TargetPoint.h"

#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Components/ArrowComponent.h"
#include <Particles/ParticleSystem.h>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnEgg.generated.h"

class UStaticMeshComponent;
class UArrowComponent;
class UDecalComponent;
class UAudioComponent;
class USoundBase;
class UParticleSystem;

UCLASS()
class MISSION_2_API ASpawnEgg : public AActor
{
	GENERATED_BODY()

protected:

	//////////////////////////
	//// Components

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* SpawnPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UAudioComponent* AudioHit;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UAudioComponent* AudioCrack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USoundBase* AudioSpawn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystem* ParticleSpawn;

	//////////////////////////
	//// Variables

	/* Array pawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn params")
	TSubclassOf<ATurtlePawn> SpawnClass;

	/* Array points */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn params")
	TArray<ATargetPoint*> PawnTrackingPoints;

	/* Timer */
	FTimerHandle TargetingTimerHandle;

protected:

	//////////////////////////
	//// Functions

	/* Initalize */
	ASpawnEgg();

	/* Begin play */
	virtual void BeginPlay() override;
	/* Spawn pawn */
	void Spawn();

public:

	/* Set point with button */
	void SetPointButton(TArray<ATargetPoint*> PointButton);
};
