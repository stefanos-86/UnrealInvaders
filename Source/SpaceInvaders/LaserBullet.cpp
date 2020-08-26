// (C) stefanos-86 - 2020 - MIT License


#include "LaserBullet.h"

#include "ConstructorHelpers.h"

ALaserBullet::ALaserBullet() 
{
	PrimaryActorTick.bCanEverTick = true;

	// TODO: copy-pasta with the spaceship load!
	Beam = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	checkf(Beam != nullptr, TEXT("Bullet mesh not created."));

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshPath(TEXT("/Game/Spaceships/Beam.Beam"));
	checkf(MeshPath.Object != nullptr, TEXT("Bullet mesh not found."));

	Beam->SetStaticMesh(MeshPath.Object);
}

void ALaserBullet::BeginPlay()
{
	Super::BeginPlay();
}

void ALaserBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float Speed = 1500;
	const float Movement = Speed * DeltaTime;
	FVector Location = GetActorLocation();
	Location.Z -= Movement;  // Very specialized movement: bullets only go "down" towards the UFOs.
	SetActorLocation(Location);

	const float MaximumRange = -1000; // TODO: set a real value
	// TODO: destroy when past max range. If location.Z < ...
}

