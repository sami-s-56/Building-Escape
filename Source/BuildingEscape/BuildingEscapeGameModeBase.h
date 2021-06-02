// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BuildingEscapeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGESCAPE_API ABuildingEscapeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	//ABuildingEscapeGameModeBase();
	UFUNCTION(BlueprintCallable, Category = "UIFunctions")
		void OnPlayButton();

	UFUNCTION(BlueprintCallable, Category = "UIFunctions")
		void OnQuitButton();

	UFUNCTION()
		void EndGame();

private:

	UPROPERTY()
		class UUserWidget* MainMenu;

	UPROPERTY()
		class UUserWidget* EndMenu;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<class UUserWidget> MainMenuAssset;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<class UUserWidget> EndMenuAsset;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void LoadMainMenu();

};
 