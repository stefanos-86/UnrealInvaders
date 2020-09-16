// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "SpaceInvadersGameModeBase.h"

#include "SpaceInvadersHUD.h"
#include "Spaceship.h"

ASpaceInvadersGameModeBase::ASpaceInvadersGameModeBase() :
	points(0), lives(3)
{
	DefaultPawnClass = ASpaceship::StaticClass();
	HUDClass = ASpaceInvadersHUD::StaticClass();
}

uint8 ASpaceInvadersGameModeBase::ScorePoint() {
	points += 1;
	// TODO: check overflow and terminate (give a "overwhelming victory" message?).
	return points;
}

uint8 ASpaceInvadersGameModeBase::LoseLife() {
	lives -= 1;
	// TODO: check when 0 and terminate (give a "game over" message).
	return lives;
}

