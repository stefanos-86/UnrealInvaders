// (C) stefanos-86 - 2020 - MIT License


#include "LaserBullet.h"

#include "Constants.h"
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

	if (Location.Z < BattlefieldFarlimit)  // TODO: there is a "Kill Z" option in the world settings. Investigate...
		Destroy();
}

