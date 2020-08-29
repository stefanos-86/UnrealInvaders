// (C) stefanos-86 - 2020 - MIT License

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlienFleet.generated.h"

UCLASS()
class SPACEINVADERS_API AAlienFleet : public AActor
{
	GENERATED_BODY()
	
public:	
	AAlienFleet();

	void LogTimer();

protected:
	virtual void BeginPlay() final;

private:
	void SpawnUfo();

	FTimerHandle TimeToNextUFO;
};
