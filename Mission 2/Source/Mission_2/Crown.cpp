#include "Crown.h"

/* Initalize */
ACrown::ACrown()
{
	PrimaryActorTick.bCanEverTick = true;

	// Body Mesh
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	RootComponent = BodyMesh;
}

/* Tick */
void ACrown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotation crown
	BodyMesh->AddLocalRotation(FRotator(0.0f, 1.0f, 0.0f));
}

