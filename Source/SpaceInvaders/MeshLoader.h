// (C) stefanos-86 - 2020 - MIT License

#pragma once

#include "UObject/Object.h"
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"

/** Common code among all the objects.
 * 
 */



class SPACEINVADERS_API MeshLoader
{
public:
	static UStaticMeshComponent* LoadMesh(const TCHAR* MeshPath, UObject* Parent);
};
