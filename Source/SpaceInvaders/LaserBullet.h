// (C) stefanos-86 - 2020 - MIT License

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"

#include "MeshLoaderComponent.h"

#include "LaserBullet.generated.h"

UCLASS()
class SPACEINVADERS_API ALaserBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ALaserBullet();
	virtual void Tick(float DeltaTime) final;
};

/* Until someone can answer the "what's the best way to make a bullet" question
(https://answers.unrealengine.com/questions/943820/view.html) I will stick to a mesh-as-projectile
approach, similar to the FPS tutorial
(https://docs.unrealengine.com/en-US/Programming/Tutorials/FirstPersonShooter/3/1/index.html). 

Also, apologize for the unusual location of this comment, but when I put it on top of the 
file (after #pragma once), the unreal header tool crashes.
*/