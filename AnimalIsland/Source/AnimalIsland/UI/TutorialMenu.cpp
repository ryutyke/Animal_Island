// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TutorialMenu.h"

#include "TitleGameMode.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GJGameInstance.h"

class ATitleGameMode;

UTutorialMenu::UTutorialMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UTutorialMenu::NativeConstruct()
{
	Super::NativeConstruct();
	StartBtn->OnClicked.AddDynamic(this, &UTutorialMenu::ClickedGameStart);
	EasyBtn->OnClicked.AddDynamic(this, &UTutorialMenu::ClickedGameStartEasy);
}

void UTutorialMenu::ClickedGameStart()
{
	if (Cast<UGJGameInstance>(GetGameInstance()) != nullptr)
	{
		Cast<UGJGameInstance>(GetGameInstance())->bIsEasy = false;
	}
	ATitleGameMode* GameMode = Cast<ATitleGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		UGameplayStatics::OpenLevel(this, FName("ThirdPersonMap"));
	}
}

void UTutorialMenu::ClickedGameStartEasy()
{
	if (Cast<UGJGameInstance>(GetGameInstance()) != nullptr)
	{
		Cast<UGJGameInstance>(GetGameInstance())->bIsEasy = true;
	}
	ATitleGameMode* GameMode = Cast<ATitleGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		UGameplayStatics::OpenLevel(this, FName("ThirdPersonMap"));
	}
}
