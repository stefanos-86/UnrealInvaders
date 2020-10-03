// (C) stefanos-86 - 2020 - MIT License

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SpaceInvadersHUD.generated.h"

/**
 * Can not do this bit in C++: I want to place my widgets in the editor, not build them 
 * 	in code. So here is the "bridge" to jump in the UI.
 */
UCLASS()
class SPACEINVADERS_API ASpaceInvadersHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateScore(const uint8 Points);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateLives(const uint8 Lives);

	UFUNCTION(BlueprintImplementableEvent)
	void EndGameMessage(const FString& Message);
};
