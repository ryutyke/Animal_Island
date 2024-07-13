// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UI/StartMenu.h"
#include "UI/TutorialMenu.h"

ATitleGameMode::ATitleGameMode()
{
	static ConstructorHelpers::FClassFinder<UStartMenu> TitleWidgetClassRef(TEXT("/Game/UI/WB_StartMenu.WB_StartMenu_C"));
	if (TitleWidgetClassRef.Class)
	{
		TitleWidgetClass = TitleWidgetClassRef.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load TitleWidgetClassRef"));
	}
	
	static ConstructorHelpers::FClassFinder<UTutorialMenu> TutorialWidgetClassRef(TEXT("/Game/UI/WB_TutorialMenu.WB_TutorialMenu_C"));
	if (TutorialWidgetClassRef.Class)
	{
		TutorialWidgetClass = TutorialWidgetClassRef.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load TutorialWidgetClassRef"));
	}
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	// UI Mode
	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(PlayerController)
	{
		FInputModeDataBase* InputMode = static_cast<FInputModeDataBase*>(new FInputModeUIOnly());
		PlayerController->SetInputMode(*InputMode);
		PlayerController->bShowMouseCursor = true;
	}

	if(TitleWidgetClass)
	{
		TitleWidget = CreateWidget<UUserWidget>(GetWorld(), TitleWidgetClass);
		if(TitleWidget)
		{
			TitleWidget->AddToViewport();
		}
	}
	if(TutorialWidgetClass)
	{
		TutorialWidget = CreateWidget<UUserWidget>(GetWorld(), TutorialWidgetClass);
		if(TutorialWidget)
		{
			TutorialWidget->AddToViewport();
			TutorialWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ATitleGameMode::TitleToTutorial()
{
	TitleWidget->SetVisibility(ESlateVisibility::Hidden);
	TutorialWidget->SetVisibility(ESlateVisibility::Visible);
}
