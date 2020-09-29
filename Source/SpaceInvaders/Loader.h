// (C) stefanos-86 - 2020 - MIT License

#pragma once

#include "UObject/Object.h"
#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"

/** Common code among many of the objects. Used to load data.
 * 
 */



class SPACEINVADERS_API Loader
{
public:
	static UStaticMeshComponent* LoadMesh(const TCHAR* MeshPath, UObject* Parent);
	static UAudioComponent* LoadSound(const TCHAR* SoundPath, UObject* Parent);
};
