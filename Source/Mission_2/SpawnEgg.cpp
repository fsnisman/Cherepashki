#include "SpawnEgg.h"
#include "Kismet/GameplayStatics.h"

/* Initalize */
ASpawnEgg::ASpawnEgg()
{
	PrimaryActorTick.bCanEverTick = true;

	// Body Mesh
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	RootComponent = BodyMesh;

	// Spawn Point
	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
	SpawnPoint->SetupAttachment(BodyMesh);

	// Audio
	AudioHit = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Hit"));
	AudioHit->SetupAttachment(BodyMesh);
	AudioCrack = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Crack"));
	AudioCrack->SetupAttachment(BodyMesh);
	AudioSpawn = CreateDefaultSubobject<USoundBase>(TEXT("Audio Spawn"));
}

/* Begin play */
void ASpawnEgg::BeginPlay()
{
	Super::BeginPlay();

	// Play audio
	AudioCrack->Play();
	// Timer Spawn
	GetWorld()->GetTimerManager().SetTimer(TargetingTimerHandle, this, &ASpawnEgg::Spawn, 1, true, 10);
}

/* Spawn pawn */
void ASpawnEgg::Spawn()
{
	// Move and spawn pawn
	FTransform SpawnTransform(SpawnPoint->GetComponentRotation(), SpawnPoint->GetComponentLocation(), FVector(1));
	ATurtlePawn* NewPawn = GetWorld()->SpawnActorDeferred<ATurtlePawn>(SpawnClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	// Move to points
	NewPawn->SetPoints(PawnTrackingPoints);

	// Check tag two
	if (ActorHasTag("Two"))
	{
		NewPawn->Tags.Add("Two");
	}

	// Check tag two
	if (ActorHasTag("Three"))
	{
		NewPawn->Tags.Add("Three");
	}

	// Finish
	UGameplayStatics::FinishSpawningActor(NewPawn, SpawnTransform);

	//Clear timer
	GetWorld()->GetTimerManager().ClearTimer(TargetingTimerHandle);

	// Spawn particle 
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSpawn, GetActorTransform());
	// Spawn audio
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioSpawn, GetActorLocation());

	SetActorEnableCollision(false);
	Destroy();
}

void ASpawnEgg::SetPointButton(TArray<ATargetPoint*> PointButton)
{
	PawnTrackingPoints = PointButton;
}

