#include "NestPawn.h"

/* Initalize */
ANestPawn::ANestPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Body Mesh
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	RootComponent = BodyMesh;
}