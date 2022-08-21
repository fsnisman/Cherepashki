/* Class nest */

#pragma once

#include "Components/StaticMeshComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NestPawn.generated.h"

UCLASS()
class MISSION_2_API ANestPawn : public APawn
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

protected:

	/* Initalize */
	ANestPawn();
};
