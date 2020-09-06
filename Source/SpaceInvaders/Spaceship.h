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

	UPROPERTY()
	UStaticMeshComponent* Mesh;

	void Move(float AxisValue);
	void Shoot();
	void Pause();
	void Quit();

	UFUNCTION()
		void BeginOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
};
