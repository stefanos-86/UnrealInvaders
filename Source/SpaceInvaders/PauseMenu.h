// (C) stefanos-86 - 2020 - MIT License

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

UCLASS()
class SPACEINVADERS_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void TogglePause(APlayerController* Controller);

	UFUNCTION(BlueprintCallable)
	void Quit(APlayerController* Controller);

	void ToUiMode(APlayerController* Controller);

private:
	void ToGameMode(APlayerController* Controller);
};
