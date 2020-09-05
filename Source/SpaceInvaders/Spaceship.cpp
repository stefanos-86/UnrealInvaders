#include "Spaceship.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Math/UnrealMathUtility.h"

#include "Constants.h"
#include "SpaceInvadersGameModeBase.h"
#include "LaserBullet.h"
#include "MeshLoader.h"

ASpaceship::ASpaceship()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = MeshLoader::LoadMesh(TEXT("/Game/Spaceships/Spaceship.Spaceship"), this);
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
		GetWorld()->SpawnActor<ALaserBullet>(GetActorLocation(), GetActorRotation());
		LastShotTime = CurrentTime;
	}
}

void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move", this, &ASpaceship::Move);

	// TODO: find a way to have continous fire without using the tick (e. g. timed callback
	// every 0.5 seconds). Drumming on the left mouse button is uncomfortable.
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ASpaceship::Shoot);


	/* This should not be there, but I could not figure out how to have another class 
	   taking input at the same time as this. */
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &ASpaceship::Pause).bExecuteWhenPaused = true;
}

void ASpaceship::Pause()
{
	// Pause() works as a toggle. Call twice, it stops the pause.
	APlayerController* Controller = GEngine->GetFirstLocalPlayerController(GetWorld());
	Controller->Pause();
	// TODO: can this stuff ever be nullptr? Kismet has checks...

	const ASpaceInvadersGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASpaceInvadersGameModeBase>();
	// TODO: pointers can be null and crash if settings are not correct (e. g. default value not set in BP game 
	// mode or game mode not set in editor project parameters).

	if (GetWorld()->IsPaused())
	{
		GameMode->PauseMenu->AddToViewport();  // TODO: find a way to bring this UI rubbish outside the spaceship. Reparent the menu and give it an "open" option?
		//FInputModeUIOnly Mode;
		FInputModeGameAndUI Mode;  // The UI only mode blocks the keyboard input from getting there. Makes sense, probably have to listen to the input in the UI itself.
	//	Mode.SetWidgetToFocus(GameMode->PauseMenu->GetCachedWidget());
		Controller->SetInputMode(Mode);
		Controller->bShowMouseCursor = true;
	}
	else
	{
		GameMode->PauseMenu->RemoveFromParent();
		FInputModeGameOnly GameMode;
		Controller->SetInputMode(GameMode);
		//FSlateApplication::Get().SetFocusToGameViewport();
		Controller->bShowMouseCursor = false;
	}
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

	// TODO: ignore laser hits. 1) Move laser out of collision area; 2) Figure out how to ignore.

	// TODO: decrement life.
}