#include "Spaceship.h"
#include "Math/UnrealMathUtility.h"

#include "Constants.h"
#include "LaserBullet.h"
#include "MeshLoader.h"

#include "Engine/Engine.h"

ASpaceship::ASpaceship()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = MeshLoader::LoadMesh(TEXT("/Game/Spaceships/Spaceship.Spaceship"), this);
	RootComponent = Mesh;
}

void ASpaceship::BeginPlay()
{
	Super::BeginPlay();
	LastShotTime = GetWorld()->GetTimeSeconds();

	Mesh->BodyInstance.SetCollisionProfileName("OverlapAll");
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ASpaceship::BeginOverlap);
}

void ASpaceship::Move(float AxisValue)
{
	const float Speed = 5;  // TODO: made configurable so that user can "adapt" to own mouse.

	const float Movement = Speed * AxisValue;

	FVector Location = GetActorLocation();
	const float NewYLocation = FMath::Clamp(Location.Y + Movement, -BattlefieldHalfWidth, BattlefieldHalfWidth);

	Location.Y = NewYLocation;
	SetActorLocation(Location);
}

void ASpaceship::Shoot()
{
	const float CooldownTime = 0.5;  // 2 shots per second.

	const float CurrentTime = GetWorld()->GetTimeSeconds();  // Could use a timer, but is it thread safe?
	if (CurrentTime > LastShotTime + CooldownTime)
	{
		GetWorld()->SpawnActor<ALaserBullet>(GetActorLocation(), GetActorRotation());
		LastShotTime = CurrentTime;
	}
}

void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move", this, &ASpaceship::Move);

	// TODO: find a way to have continous fire without using the tick (e. g. timed callback
	// every 0.5 seconds). Drumming on the left mouse button is uncomfortable.
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ASpaceship::Shoot);
}


void ASpaceship::BeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("Spaceship overlap"));
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("Spaceship overlap"));
}