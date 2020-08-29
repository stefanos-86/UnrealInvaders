#include "Spaceship.h"
#include "Math/UnrealMathUtility.h"

#include "LaserBullet.h"
#include "MeshLoader.h"

ASpaceship::ASpaceship()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = MeshLoader::LoadMesh(TEXT("/Game/Spaceships/Spaceship.Spaceship"), this);
}

void ASpaceship::BeginPlay()
{
	Super::BeginPlay();
	LastShotTime = GetWorld()->GetTimeSeconds();
}

void ASpaceship::Move(float AxisValue)
{
	const float Speed = 5;  // TODO: made configurable so that user can "adapt" to own mouse.

	// The camera is positioned as to allow this much space of movement.
	// It should be possible to understand the limit of the frame with some math related
	// to the camera position, rotation and FOV, but that is overkill.
	const float MaxMovementExtent = 800;

	const float Movement = Speed * AxisValue;

	FVector Location = GetActorLocation();
	const float NewYLocation = FMath::Clamp(Location.Y + Movement, -MaxMovementExtent, MaxMovementExtent);

	Location.Y = NewYLocation;
	SetActorLocation(Location);
}

void ASpaceship::Shoot()
{
	const float CooldownTime = 0.5;  // 2 shots per second.

	const float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime > LastShotTime + CooldownTime)
	{
		// Rotation does not really count here. Bullet is a sphere, movement is fixed.
		GetWorld()->SpawnActor<ALaserBullet>(GetActorLocation(), GetActorRotation());
		LastShotTime = CurrentTime;
	}
}

// Called to bind functionality to input
void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move", this, &ASpaceship::Move);

	// TODO: find a way to have continous fire without using the tick (e. g. timed callback
	// every 0.5 seconds). Drumming on the left mouse button is uncomfortable.
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ASpaceship::Shoot);
}
