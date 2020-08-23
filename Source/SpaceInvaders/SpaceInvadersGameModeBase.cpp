// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "SpaceInvadersGameModeBase.h"

#include "Spaceship.h"

ASpaceInvadersGameModeBase::ASpaceInvadersGameModeBase() :
	points(0),
	lives(3)
{
	DefaultPawnClass = ASpaceship::StaticClass();
}