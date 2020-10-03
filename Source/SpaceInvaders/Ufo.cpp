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

	// Copy of the laser bullet movement, opposite direction. Should refactor is a single place.
	const float Speed = 800;
	const float Movement = Speed * DeltaTime;
	FVector Location = GetActorLocation();
	Location.Z += Movement;
	SetActorLocation(Location);

	if (Location.Z > BattlefieldNearlimit) {
		Destroy();
		GetHud()->UpdateScore(GetMode()->LosePoint());
	}
}

void AUfo::BeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult) 
{
	ASpaceInvadersHUD* Hud = GetHud();
	ASpaceInvadersGameModeBase* GameMode = GetMode();
	Hud->UpdateScore(GameMode->ScorePoint());

	checkf(CrashSound != nullptr, TEXT("Sound not created.")); // Has to be tested here, sounds only created in play, not in editor.
	CrashSound->Play();

	if (GameMode->Victory()) {
		APlayerController* Controller = GEngine->GetFirstLocalPlayerController(GetWorld());
		Controller->Pause();
		GameMode->PauseMenu->ToUiMode(Controller);
		Hud->EndGameMessage(TEXT("You saved the universe!"));  // TODO: duplicated in spaceship. Refactor in game hud?
	}

	Destroy();
}



ASpaceInvadersGameModeBase* AUfo::GetMode()
{
	return  GetWorld()->GetAuthGameMode<ASpaceInvadersGameModeBase>();
}

ASpaceInvadersHUD* AUfo::GetHud()
{
	return Cast<ASpaceInvadersHUD>(GEngine->GetFirstLocalPlayerController(GetWorld())->GetHUD());
}
