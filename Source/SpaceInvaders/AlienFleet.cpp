// (C) stefanos-86 - 2020 - MIT License


#include "AlienFleet.h"

#include "Ufo.h"

AAlienFleet::AAlienFleet()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAlienFleet::BeginPlay()
{
	Super::BeginPlay();

	// Fire out UFOs without pause!
	const float TimeBetweenSpawning_seconds = 3;
	const bool Repeat = true;

	GetWorldTimerManager().SetTimer(
		TimeToNextUFO,
		this, &AAlienFleet::SpawnUfo,
		TimeBetweenSpawning_seconds, Repeat);
}

void AAlienFleet::SpawnUfo()
{
	// Constant rotation: who cares, the UFO is round...
	const FRotator NoRotation(0, 0, 0);

	// TODO write the algo to have the locations.

	GetWorld()->SpawnActor<AUfo>(FVector(0, 0, -800), NoRotation);
}


