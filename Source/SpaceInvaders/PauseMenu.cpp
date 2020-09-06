// (C) stefanos-86 - 2020 - MIT License


#include "PauseMenu.h"

void UPauseMenu::TogglePause(APlayerController* Controller)
{
	Controller->Pause(); // Pause() works as a toggle. Call twice, it stops the pause.

	// TODO: pointers can be null and crash if settings are not correct (e. g. default value not set in BP game 
	// mode or game mode not set in editor project parameters).

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