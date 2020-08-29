// (C) stefanos-86 - 2020 - MIT License


#include "MeshLoader.h"

#include "ConstructorHelpers.h"

UStaticMeshComponent* MeshLoader::LoadMesh(const TCHAR* MeshPath, UObject* Parent)
{
	UStaticMeshComponent* Mesh = Parent->CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	checkf(Mesh != nullptr, TEXT("Mesh not created."));  // TODO: concantenate the mesh path!

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshPathObject(MeshPath);
	checkf(MeshPathObject.Object != nullptr, TEXT("Mesh not found.")); // TODO: concantenate the mesh path!

	Mesh->SetStaticMesh(MeshPathObject.Object);
	
	return Mesh;
}
