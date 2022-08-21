/* Class crown */

#pragma once

#include "Components/StaticMeshComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Crown.generated.h"

UCLASS()
class MISSION_2_API ACrown : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

public:
	/* Initalize */
	ACrown();

public:
	/* Tick */
	virtual void Tick(float DeltaTime) override;

};
