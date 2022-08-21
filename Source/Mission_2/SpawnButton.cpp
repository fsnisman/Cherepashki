#include "SpawnButton.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

/* Initalize */
ASpawnButton::ASpawnButton()
{
	PrimaryActorTick.bCanEverTick = true;

	// Body Mesh
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	RootComponent = BodyMesh;

	// Hit Collider
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Hit Collider"));
	SphereCollider->SetupAttachment(RootComponent);
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ASpawnButton::OnMeshOverlapBegin);
	SphereCollider->OnComponentEndOverlap.AddDynamic(this, &ASpawnButton::OnOverlapEnd);

	// Spawn Point
	SpawnPointNest = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point Nest"));
	SpawnPointNest->SetupAttachment(RootComponent);
	SpawnPointEgg = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point Egg"));
	SpawnPointEgg->SetupAttachment(RootComponent);

	// Text
	TextNumber = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Number"));
	TextNumber->SetupAttachment(BodyMesh);
	TextInteractive = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Interactive"));
	TextInteractive->SetupAttachment(BodyMesh);

	// Audio
	AudioSpawnEgg = CreateDefaultSubobject<USoundBase>(TEXT("Audio Spawn Egg"));
	AudioSpawnNest = CreateDefaultSubobject<USoundBase>(TEXT("Audio Spawn Nest"));
	AudioPress = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Press"));
	AudioPress->SetupAttachment(BodyMesh);

	// Particle
	ParticleSpawnNest = CreateDefaultSubobject<UParticleSystem>(TEXT("Partical Spawn Nest"));
	ParticleSpawnEgg = CreateDefaultSubobject<UParticleSystem>(TEXT("Partical Spawn Egg"));
}

void ASpawnButton::BeginPlay()
{
	//Super::BeginPlay();

	if (ActorHasTag("One"))
	{
		TextNumber->SetText(FText::FromString("1"));
	}

	if(ActorHasTag("Two"))
	{
		TextNumber->SetText(FText::FromString("2"));
	}

	if(ActorHasTag("Three"))
	{
		TextNumber->SetText(FText::FromString("3"));
	}

	TextInteractive->SetVisibility(false);
}

/* Colliison Event Begin */
void ASpawnButton::OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerPawn = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if (OtherActor == PlayerPawn)
	{
		// Enable text
		TextInteractive->SetVisibility(true);
	}
}

/* Colliison Event End*/
void ASpawnButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* PlayerPawn = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if (OtherActor == PlayerPawn)
	{
		// Disable text
		TextInteractive->SetVisibility(false);
	}

}

/* Timer Start spawn */
void ASpawnButton::StartSpawn()
{
	// Play audio
	AudioPress->Play();
	//Timer Spawn
	GetWorld()->GetTimerManager().SetTimer(TargetingTimerHandle, this, &ASpawnButton::SpawnNests, 1, true, 1);
}

/* Spawn Nests */
void ASpawnButton::SpawnNests()
{
	// Spawn pawn
	FTransform SpawnTransform(SpawnPointNest->GetComponentRotation(), SpawnPointNest->GetComponentLocation(), FVector(1));
	ANestPawn* NewPawn = GetWorld()->SpawnActorDeferred<ANestPawn>(SpawnNest, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	// Spawn audio
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioSpawnNest, NewPawn->GetActorLocation());
	// Spawn particle
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSpawnNest, NewPawn->GetActorTransform());

	// Timer Spawn
	GetWorld()->GetTimerManager().SetTimer(TargetingTimerHandle, this, &ASpawnButton::SpawnEggs, 1, true, 5);
}

/* Spawn Eggs */
void ASpawnButton::SpawnEggs()
{
	// Spawn pawn
	FTransform SpawnTransform(SpawnPointEgg->GetComponentRotation(), SpawnPointEgg->GetComponentLocation(), FVector(1));
	ASpawnEgg* NewPawn = GetWorld()->SpawnActorDeferred<ASpawnEgg>(SpawnEgg, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	// Set travel point
	NewPawn->SetPointButton(PawnTrackingPoints);

	// Check tag two
	if(ActorHasTag("Two"))
	{
		NewPawn->Tags.Add("Two");
	}

	// Check tag Tree
	if (ActorHasTag("Three"))
	{
		NewPawn->Tags.Add("Three");
	}

	// Finish
	UGameplayStatics::FinishSpawningActor(NewPawn, SpawnTransform);

	// Spawn audio
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioSpawnEgg, NewPawn->GetActorLocation());
	// Spawn particle
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSpawnEgg, NewPawn->GetActorTransform());

	//Clear timer
	GetWorld()->GetTimerManager().ClearTimer(TargetingTimerHandle);

	Destroy();
}



