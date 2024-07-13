// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"

#include "AnimalIslandGameMode.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainMenu::OnPressedEscBtn()
{
	AAnimalIslandGameMode* GameMode = Cast<AAnimalIslandGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->ViewSettingUI();
	}
}