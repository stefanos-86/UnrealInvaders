// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "SpaceInvadersGameModeBase.h"

#include "SpaceInvadersHUD.h"
#include "Spaceship.h"

ASpaceInvadersGameModeBase::ASpaceInvadersGameModeBase() 
{
	DefaultPawnClass = ASpaceship::StaticClass();
	HUDClass = ASpaceInvadersHUD::StaticClass();
}

uint8 ASpaceInvadersGameModeBase::ScorePoint() {
	points += 1;
	// TODO: check overflow and terminate (give a "overwhelming victory" message?).
	return points;
}

