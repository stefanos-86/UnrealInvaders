// (C) stefanos-86 - 2020 - MIT License


#include "LaserBullet.h"

#include "Constants.h"
#include "Loader.h"

ALaserBullet::ALaserBullet() 
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = Loader::LoadMesh(TEXT("/Game/Spaceships/Beam.Beam"), this);
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

	if (Location.Z < BattlefieldFarlimit)
		Destroy();
}

