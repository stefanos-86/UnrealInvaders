// (C) stefanos-86 - 2020 - MIT License


#include "LaserBullet.h"

#include "ConstructorHelpers.h"

ALaserBullet::ALaserBullet() 
{
	PrimaryActorTick.bCanEverTick = true;

	// TODO: copy-pasta with the spaceship load! But where can I put a common method?
	// It can't be in an helper or in a static, because I want a default sup object of "this".
	// Use multiple inheritance? A common base class (but I have a pawn and an actor...)?
	Beam = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	checkf(Beam != nullptr, TEXT("Bullet mesh not created."));

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshPath(TEXT("/Game/Spaceships/Beam.Beam"));
	checkf(MeshPath.Object != nullptr, TEXT("Bullet mesh not found."));

	Beam->SetStaticMesh(MeshPath.Object);
	RootComponent = Beam;
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

	const float MaximumRange = -2500; // This is where the starfield originates.
	if (Location.Z < MaximumRange)
		Destroy();
}

