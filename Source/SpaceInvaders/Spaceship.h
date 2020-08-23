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
	UPROPERTY()
	UStaticMeshComponent* SpaceshipMesh;

	void LoadMesh(const TCHAR* path);
	void Move(float AxisValue);
};
