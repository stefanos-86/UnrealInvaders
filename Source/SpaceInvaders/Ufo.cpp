// (C) stefanos-86 - 2020 - MIT License


#include "Ufo.h"

#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

AUfo::AUfo()
{
	PrimaryActorTick.bCanEverTick = true;

	UfoMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	checkf(UfoMesh != nullptr, TEXT("Spaceship mesh not created."));

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshPath(TEXT("/Game/Spaceships/UFO.UFO"));
	checkf(MeshPath.Object != nullptr, TEXT("Spaceship mesh not found."));

	UfoMesh->SetStaticMesh(MeshPath.Object);
}

void AUfo::BeginPlay()
{
	Super::BeginPlay();
	
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

	const float MaximumRange = +300;
	if (Location.Z > MaximumRange)
		Destroy();
		// TODO: score points for the UFOs.


	// TODO: fire for the UFO.
}

