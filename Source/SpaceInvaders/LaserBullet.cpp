// (C) stefanos-86 - 2020 - MIT License


#include "LaserBullet.h"

#include "Constants.h"
#include "Loader.h"

ALaserBullet::ALaserBullet() 
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = Loader::LoadMesh(TEXT("/Game/Spaceships/Beam.Beam"), this);
	RootComponent = Mesh;
}


void ALaserBullet::BeginPlay()
{
	Super::BeginPlay();

	Mesh->BodyInstance.SetCollisionProfileName("OverlapAll");
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ALaserBullet::BeginOverlap);
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


void ALaserBullet::BeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, TEXT("LASER overlap"));
	Destroy();
}

