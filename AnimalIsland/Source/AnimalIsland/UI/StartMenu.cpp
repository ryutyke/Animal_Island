// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StartMenu.h"

#include "Components/Button.h"
#include "AnimalIslandGameMode.h"

UStartMenu::UStartMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UStartMenu::NativeConstruct()
{
	Super::NativeConstruct();
	StartBtn->OnClicked.AddDynamic(this, &UStartMenu::ClickedGameStart);
	SettingBtn->OnClicked.AddDynamic(this, &UStartMenu::ClickedSettings);
}

void UStartMenu::ClickedGameStart()
{
	// need modifying
	AAnimalIslandGameMode* GameMode = Cast<AAnimalIslandGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		//GameMode->ViewTutorialUI();
	}
}

void UStartMenu::ClickedSettings()
{
	AAnimalIslandGameMode* GameMode = Cast<AAnimalIslandGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->ViewSettingUI();
	}
}
