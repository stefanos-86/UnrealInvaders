// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "PauseMenu.h"

#include "SpaceInvadersGameModeBase.generated.h"

UCLASS()
class SPACEINVADERS_API ASpaceInvadersGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASpaceInvadersGameModeBase();

	/** Bridge between C++ and the blueprint menu. Not sure the game mode is the
	    right place to host the reference. Maybe a singleton somewhere. 
		This sadly forces the game mode to be a blueprint, but there is no other way
		unless I add an object in the scene and link the blueprint to it in the editor.
		But that, you have to do for every map. This, only once in the game mode blueprint.*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPauseMenu* PauseMenu;
};
