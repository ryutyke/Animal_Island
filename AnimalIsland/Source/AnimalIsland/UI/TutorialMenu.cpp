// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TutorialMenu.h"

#include "TitleGameMode.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

class ATitleGameMode;

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
	ATitleGameMode* GameMode = Cast<ATitleGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		UGameplayStatics::OpenLevel(this, FName("ThirdPersonMap"));
	}
}
