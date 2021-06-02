// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingEscapeGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

void ABuildingEscapeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	LoadMainMenu();
}

void ABuildingEscapeGameModeBase::LoadMainMenu()
{
	if (MainMenuAssset)
	{
		MainMenu = CreateWidget<UUserWidget>(GetWorld(), MainMenuAssset);
		if (MainMenu)
		{
			MainMenu->AddToViewport();
			MainMenu->SetVisibility(ESlateVisibility::Visible);
		}

		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
}

void ABuildingEscapeGameModeBase::OnPlayButton() 
{
	if (MainMenu)
	{
		MainMenu->RemoveFromViewport();
	}
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
}

void ABuildingEscapeGameModeBase::OnQuitButton() 
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void ABuildingEscapeGameModeBase::EndGame()
{
	if (EndMenuAsset)
	{
		EndMenu = CreateWidget<UUserWidget>(GetWorld(), EndMenuAsset);
		if (EndMenu)
		{
			EndMenu->AddToViewport();
			EndMenu->SetVisibility(ESlateVisibility::Visible);
		}
		
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
}
