// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "SpaceInvadersGameModeBase.h"

#include "SpaceInvadersHUD.h"
#include "Spaceship.h"

ASpaceInvadersGameModeBase::ASpaceInvadersGameModeBase() :
	points(0), lives(3), pointsToWin(10)
{
	DefaultPawnClass = ASpaceship::StaticClass();
	HUDClass = ASpaceInvadersHUD::StaticClass();
}

uint8 ASpaceInvadersGameModeBase::ScorePoint() {
	checkf(points < pointsToWin, TEXT("Victory achieved, but game not stopped."));

	points += 1;
	return points;
}

uint8 ASpaceInvadersGameModeBase::LosePoint() {
	if (points > 0)
		points-= 1;
	// Let's be generous and don't allow epic defeats with negative points.

	return points;
}

uint8 ASpaceInvadersGameModeBase::LoseLife() {
	checkf(lives > 0, TEXT("0 lives but game not ended."));
	
	lives -= 1;
	return lives;
}

bool ASpaceInvadersGameModeBase::Dead() const {
	return lives == 0;
}

bool ASpaceInvadersGameModeBase::Victory() const {
	return points == pointsToWin;
}
