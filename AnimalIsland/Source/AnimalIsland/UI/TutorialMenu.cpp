// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TutorialMenu.h"

#include "AnimalIslandGameMode.h"
#include "Components/Button.h"

UTutorialMenu::UTutorialMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UTutorialMenu::NativeConstruct()
{
	Super::NativeConstruct();
	StartBtn->OnClicked.AddDynamic(this, &UTutorialMenu::ClickedGameStart);
}

void UTutorialMenu::ClickedGameStart()
{
	AAnimalIslandGameMode* GameMode = Cast<AAnimalIslandGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->StartMainUI();
	}
}
