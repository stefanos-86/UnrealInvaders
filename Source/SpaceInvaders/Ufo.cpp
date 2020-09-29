// (C) stefanos-86 - 2020 - MIT License


#include "Ufo.h"

#include "Engine/Engine.h"
#include "Sound/SoundBase.h"

#include "Constants.h"
#include "Loader.h"
#include "SpaceInvadersGameModeBase.h"
#include "SpaceInvadersHUD.h"


AUfo::AUfo()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = Loader::LoadMesh(TEXT("/Game/Spaceships/UFO.UFO"), this);
	CrashSound = Loader::LoadSound(TEXT("/Game/Sound/impact.impact"), this);

	RootComponent = Mesh;
}

void AUfo::BeginPlay()
{
	Super::BeginPlay();

	Mesh->BodyInstance.SetCollisionProfileName("OverlapAll");
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AUfo::BeginOverlap);
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

void AUfo::BeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult) 
{

	UE_LOG(LogTemp, Warning, TEXT("UFO overlap"));
	GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, TEXT("UFO overlap"));

	ASpaceInvadersGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASpaceInvadersGameModeBase>();
	// TODO Use a binding? So far, this is the only place where the score can change...
	ASpaceInvadersHUD* Hud = Cast<ASpaceInvadersHUD>(GEngine->GetFirstLocalPlayerController(GetWorld())->GetHUD());
	Hud->UpdateScore(GameMode->ScorePoint());

	checkf(CrashSound != nullptr, TEXT("Sound not created.")); // Has to be tested here, sounds only created in play, not in editor.
	CrashSound->Play();

	Destroy();

	// TODO: destroy laser bullet as well.

}
