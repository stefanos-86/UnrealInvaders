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

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	UStaticMeshComponent* UfoMesh;

};