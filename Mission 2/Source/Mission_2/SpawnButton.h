/* Class button spawn egg */

#pragma once

#include "SpawnEgg.h"
#include "NestPawn.h"

#include "Components/TextRenderComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/InputComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnButton.generated.h"

class UStaticMeshComponent;
class UAudioComponent;
class USphereComponent;
class UArrowComponent;
class USoundBase;

UCLASS()
class MISSION_2_API ASpawnButton : public AActor
{
	GENERATED_BODY()

protected:

	//////////////////////////
	//// Components
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* SpawnPointNest;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* SpawnPointEgg;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USphereComponent* SphereCollider;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* TextNumber;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* TextInteractive;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USoundBase* AudioSpawnEgg;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USoundBase* AudioSpawnNest;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystem* ParticleSpawnEgg;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystem* ParticleSpawnNest;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UAudioComponent* AudioPress;

	//////////////////////////
	//// Variables

	/* Array actor spawn */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn params")
	TSubclassOf<ASpawnEgg> SpawnEgg;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn params")
	TSubclassOf<ANestPawn> SpawnNest;

	/* Array points */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn params")
	TArray<ATargetPoint*> PawnTrackingPoints;

	/* Timer */
	FTimerHandle TargetingTimerHandle;

protected:

	/* Initalize */
	ASpawnButton();
	/* Begin play */
	virtual void BeginPlay() override;

	/* Collision event */
	UFUNCTION()
	void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

	/* Spawn Eggs */
	void SpawnEggs();
	/* Spawn Nests */
	void SpawnNests();
	/* Spawn start time */
	void StartSpawn();
};
