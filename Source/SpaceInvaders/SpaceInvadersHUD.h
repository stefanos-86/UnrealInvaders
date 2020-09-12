// (C) stefanos-86 - 2020 - MIT License

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SpaceInvadersHUD.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERS_API ASpaceInvadersHUD : public AHUD
{
	GENERATED_BODY()

public:
	/** Can not do in C++: I want to place my widgets in the editor, not build them 
	    in code. So here is the "bridge" to jump in the UI.*/
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateScore(const uint8 Points);
	
};
