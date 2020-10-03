// (C) stefanos-86 - 2020 - MIT License


#include "AlienFleet.h"

#include "Math/UnrealMathUtility.h"

#include "Constants.h"
#include "Ufo.h"

AAlienFleet::AAlienFleet()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAlienFleet::BeginPlay()
{
	Super::BeginPlay();

	// Fire out UFOs without pause!
	const float TimeBetweenSpawning_seconds = 1;
	const bool Repeat = true;

	GetWorldTimerManager().SetTimer(
		TimeToNextUFO,
		this, &AAlienFleet::SpawnUfo,
		TimeBetweenSpawning_seconds, Repeat);
}

void AAlienFleet::SpawnUfo()
{

	const float UfoLateralPosition = FMath::FRandRange(-BattlefieldHalfWidth, BattlefieldHalfWidth);

	// Assume that the UFOs go away fast enough to avoid overlaps. This may change in the future.
	
	const FVector UfoStartPosition(0, UfoLateralPosition, BattlefieldFarlimit);

	// Constant rotation: who cares, the UFO is round...
	const FRotator NoRotation(0, 0, 0);

	GetWorld()->SpawnActor<AUfo>(UfoStartPosition, NoRotation);
}


