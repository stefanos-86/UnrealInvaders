#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Spaceship.generated.h"

UCLASS()
class SPACEINVADERS_API ASpaceship : public APawn
{
	GENERATED_BODY()

public:
	ASpaceship();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) final;

protected:
	virtual void BeginPlay() final;

private:
	float LastShotTime;

	void Move(float AxisValue);
	void Shoot();
};
