// (C) stefanos-86 - 2020 - MIT License


#include "PauseMenu.h"

void UPauseMenu::TogglePause(APlayerController* Controller)
{
	// Pointers can be null and crash if settings are not correct (e. g. default value not set in BP game 
	// mode or game mode not set in editor project parameters).
	checkf(Controller != nullptr, TEXT("No player controller."));

	Controller->Pause(); // Pause() works as a toggle. Call twice, it stops the pause.

	if (GetWorld()->IsPaused())
	{
		AddToViewport(); 
		// The UI only mode blocks the keyboard input. 
		//But the controller can still quit and pause with the keyboard.
		FInputModeGameAndUI Mode; 
		Controller->SetInputMode(Mode);
		Controller->bShowMouseCursor = true;
	}
	else
	{
		RemoveFromParent();
		FInputModeGameOnly GameMode;
		Controller->SetInputMode(GameMode);
		Controller->bShowMouseCursor = false;
	}
}

void UPauseMenu::Quit(APlayerController* Controller)
{
	// Console command??? The Internet says this is the way. Kismet does a similar thing.
	Controller->ConsoleCommand("Quit");
}