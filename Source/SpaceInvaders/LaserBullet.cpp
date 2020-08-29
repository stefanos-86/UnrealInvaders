// (C) stefanos-86 - 2020 - MIT License


#include "LaserBullet.h"

#include "MeshLoader.h"

ALaserBullet::ALaserBullet() 
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = MeshLoader::LoadMesh(TEXT("/Game/Spaceships/Beam.Beam"), this);
}

void ALaserBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Very specialized movement: bullets only go "down" towards the UFOs.
	const float Speed = 1500;
	const float Movement = Speed * DeltaTime;
	FVector Location = GetActorLocation();
	Location.Z -= Movement;  
	SetActorLocation(Location);

	const float MaximumRange = -2500; // This is where the starfield originates.
	if (Location.Z < MaximumRange)
		Destroy();
}

