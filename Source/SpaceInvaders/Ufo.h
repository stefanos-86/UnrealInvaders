// (C) stefanos-86 - 2020 - MIT License

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ufo.generated.h"

UCLASS()
class SPACEINVADERS_API AUfo : public AActor
{
	GENERATED_BODY()
	
public:	
	AUfo();
	virtual void Tick(float DeltaTime) final;

protected:
	virtual void BeginPlay() final;

private:
	UPROPERTY()
	UStaticMeshComponent* Mesh;

	UFUNCTION()
	void BeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
