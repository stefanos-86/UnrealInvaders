// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "SpaceInvadersGameModeBase.h"

#include "Spaceship.h"

ASpaceInvadersGameModeBase::ASpaceInvadersGameModeBase() 
{
	DefaultPawnClass = ASpaceship::StaticClass();
}