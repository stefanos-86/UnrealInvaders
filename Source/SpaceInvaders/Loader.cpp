// (C) stefanos-86 - 2020 - MIT License


#include "Loader.h"

#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

UStaticMeshComponent* Loader::LoadMesh(const TCHAR* MeshPath, UObject* Parent)
{
	UStaticMeshComponent* Mesh = Parent->CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	checkf(Mesh != nullptr, TEXT("Mesh not created."));  // TODO: concantenate the mesh path!

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshPathObject(MeshPath);
	checkf(MeshPathObject.Object != nullptr, TEXT("Mesh not found.")); // TODO: concantenate the mesh path!

	Mesh->SetStaticMesh(MeshPathObject.Object);
	
	return Mesh;
}

UAudioComponent* Loader::LoadSound(const TCHAR* SoundPath, UObject* Parent)
{

	ConstructorHelpers::FObjectFinder<USoundBase> SoundPathObject(SoundPath);
	checkf(SoundPathObject.Object != nullptr, TEXT("Sound not found."));  // TODO: say what sound is not found.

	UAudioComponent* Sound = UGameplayStatics::SpawnSoundAtLocation(Parent, SoundPathObject.Object, FVector::ZeroVector);
	
	// Crashes the editor! Sound not created in editor mode.
	// checkf(LaserSound != nullptr, TEXT("Sound not created."));

	// Immediately stop playing the sound, otherwise you hear it when the game starts.
	// This is not "proper", but the alternative is to copy-paste SpawnSoundAtLocation, minus the
	// call to the play method.
	if (Sound)
		Sound->Stop();

	return Sound;
}
