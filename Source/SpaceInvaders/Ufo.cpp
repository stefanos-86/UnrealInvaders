// (C) stefanos-86 - 2020 - MIT License


#include "Ufo.h"

#include "Constants.h"
#include "MeshLoader.h"

AUfo::AUfo()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = MeshLoader::LoadMesh(TEXT("/Game/Spaceships/UFO.UFO"), this);
}

void AUfo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// For now, simplified movement. Just advance. TODO: make zig-zag patterns.
	// It is a copy of the laser bullet, but it will "go away", it's just temporary code.
	const float Speed = 700;
	const float Movement = Speed * DeltaTime;
	FVector Location = GetActorLocation();
	Location.Z += Movement;
	SetActorLocation(Location);

	if (Location.Z > BattlefieldNearlimit)
		Destroy();
		// TODO: score points for the UFOs.


	// TODO: fire for the UFO.
}

