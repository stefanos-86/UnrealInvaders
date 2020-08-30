#include "Spaceship.h"
#include "Math/UnrealMathUtility.h"

#include "Constants.h"
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

// Called to bind functionality to input
void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move", this, &ASpaceship::Move);

	// TODO: find a way to have continous fire without using the tick (e. g. timed callback
	// every 0.5 seconds). Drumming on the left mouse button is uncomfortable.
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ASpaceship::Shoot);
}
