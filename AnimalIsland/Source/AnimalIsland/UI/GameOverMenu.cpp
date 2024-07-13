// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameOverMenu.h"

#include "AnimalIslandGameMode.h"
#include "Components/Button.h"

UGameOverMenu::UGameOverMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UGameOverMenu::NativeConstruct()
{
	Super::NativeConstruct();

	BackBtn->OnClicked.AddDynamic(this, &UGameOverMenu::ClickedBackBtn);
}

void UGameOverMenu::ClickedBackBtn()
{
	AAnimalIslandGameMode* GameMode = Cast<AAnimalIslandGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->GameoverToTitleUI();
	}
}
