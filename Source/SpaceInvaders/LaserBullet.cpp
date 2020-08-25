// (C) stefanos-86 - 2020 - MIT License


#include "LaserBullet.h"

ALaserBullet::ALaserBullet() 
{
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("ColliderForBullet"));
	checkf(Collider != nullptr, TEXT("Collision mesh for bullet not created."));

	// Shpere is INVISIBLE: use show Collision in console until a visible mesh is available.

	Collider->InitSphereRadius(15.0f);
	RootComponent = Collider;
}

void ALaserBullet::BeginPlay()
{
	Super::BeginPlay();
}

void ALaserBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float Speed = 1000;
	const float Movement = Speed * DeltaTime;
	FVector Location = GetActorLocation();
	Location.Z -= Movement;  // Very specialized movement: bullets only go "down" towards the UFOs.
	SetActorLocation(Location);

	const float MaximumRange = -1000; // TODO: set a real value
	// TODO: destroy when past max range. If location.Z < ...
}

