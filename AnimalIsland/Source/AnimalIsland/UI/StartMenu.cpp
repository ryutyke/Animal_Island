// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StartMenu.h"

#include "Components/Button.h"
#include "TitleGameMode.h"

UStartMenu::UStartMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UStartMenu::NativeConstruct()
{
	Super::NativeConstruct();
	StartBtn->OnClicked.AddDynamic(this, &UStartMenu::ClickedGameStart);
}

void UStartMenu::ClickedGameStart()
{
	// need modifying
	ATitleGameMode* GameMode = Cast<ATitleGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->TitleToTutorial();
	}
}

