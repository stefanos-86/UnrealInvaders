#include "Spaceship.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Math/UnrealMathUtility.h"
#include "Sound/SoundBase.h"

#include "Constants.h"
#include "SpaceInvadersGameModeBase.h"
#include "SpaceInvadersHUD.h"
#include "LaserBullet.h"
#include "Loader.h"

ASpaceship::ASpaceship()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = Loader::LoadMesh(TEXT("/Game/Spaceships/Spaceship.Spaceship"), this);
	LaserSound = Loader::LoadSound(TEXT("/Game/Sound/gunShot.gunShot"), this);
	
	RootComponent = Mesh;
}

void ASpaceship::BeginPlay()
{
	Super::BeginPlay();
	LastShotTime = GetWorld()->GetTimeSeconds();

	Mesh->BodyInstance.SetCollisionProfileName("OverlapAll");
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ASpaceship::BeginOverlap);
}

void ASpaceship::Move(float AxisValue)
{
	const float Speed = 5;  // TODO: made configurable so that user can "adapt" to own mouse.

	const float Movement = Speed * AxisValue;

	FVector Location = GetActorLocation();
	const float NewYLocation = FMath::Clamp(Location.Y + Movement, -BattlefieldHalfWidth, BattlefieldHalfWidth);

	Location.Y = NewYLocation;
	SetActorLocation(Location);
}

void ASpaceship::Shoot()
{
	const float CooldownTime = 0.5;  // 2 shots per second.

	const float CurrentTime = GetWorld()->GetTimeSeconds();  // Could use a timer, but is it thread safe?
	if (CurrentTime > LastShotTime + CooldownTime)
	{
		const FVector LaserStartLocation = Mesh->GetSocketLocation("LaserStartPoint");
		GetWorld()->SpawnActor<ALaserBullet>(LaserStartLocation, GetActorRotation());
		LastShotTime = CurrentTime;

		checkf(LaserSound != nullptr, TEXT("Sound not created.")); // Has to be tested here, sounds only created in play, not in editor.
		LaserSound->Play();
	}	
}

void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move", this, &ASpaceship::Move);

	// TODO: find a way to have continous fire without using the tick (e. g. timed callback
	// every 0.5 seconds). Drumming on the left mouse button is uncomfortable.
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ASpaceship::Shoot);


	/* There should not be there, but I could not figure out how to have another class 
	   taking input at the same time as this. */
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &ASpaceship::Pause).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("Quit", IE_Pressed, this, &ASpaceship::Quit).bExecuteWhenPaused = true;
}

void ASpaceship::Pause()
{
	GetGameMode()->PauseMenu->TogglePause(GetController());
}

void ASpaceship::Quit() {
	GetGameMode()->PauseMenu->Quit(GetController());
}

APlayerController* ASpaceship::GetController() const
{
	return GEngine->GetFirstLocalPlayerController(GetWorld());
}

ASpaceInvadersGameModeBase* ASpaceship::GetGameMode()
{
	return GetWorld()->GetAuthGameMode<ASpaceInvadersGameModeBase>();
}

void ASpaceship::BeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("Spaceship overlap"));
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("Spaceship overlap"));

	ASpaceInvadersHUD* Hud = Cast<ASpaceInvadersHUD>(GEngine->GetFirstLocalPlayerController(GetWorld())->GetHUD());
	Hud->UpdateLives(GetGameMode()->LoseLife());
}