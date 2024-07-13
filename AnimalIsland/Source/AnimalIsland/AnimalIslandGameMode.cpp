// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimalIslandGameMode.h"
#include "AnimalIslandCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "UI/StartMenu.h"
#include "UI/TutorialMenu.h"
#include "UI/MainMenu.h"
#include "UI/SettingMenu.h"
#include "UI/GameOverMenu.h"

AAnimalIslandGameMode::AAnimalIslandGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_Character"));
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

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

	static ConstructorHelpers::FClassFinder<UMainMenu> MainWidgetClassRef(TEXT("/Game/UI/WB_MainMenu.WB_MainMenu_C"));
	if (MainWidgetClassRef.Class)
	{
		MainWidgetClass = MainWidgetClassRef.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load MainWidgetClassRef"));
	}
	
	static ConstructorHelpers::FClassFinder<USettingMenu> SettingWidgetRef(TEXT("/Game/UI/WB_SettingMenu.WB_SettingMenu_C"));
	if (SettingWidgetRef.Class)
	{
		SettingWidgetClass = SettingWidgetRef.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load SettingWidgetClass"));
	}

	static ConstructorHelpers::FClassFinder<UGameOverMenu> GameoverWidgetRef(TEXT("/Game/UI/WB_GameOverMenu.WB_GameOverMenu_C"));
	if (GameoverWidgetRef.Class)
	{
		GameoverWidgetClass = GameoverWidgetRef.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load GameOverWidgetClass"));
	}
}

void AAnimalIslandGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Pause Game
	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(PlayerController)
	{
		PlayerController->SetPause(true);
		FInputModeDataBase* InputMode = static_cast<FInputModeDataBase*>(new FInputModeUIOnly());
		PlayerController->SetInputMode(*InputMode);
	}
	// Start with Title
	if(TitleWidget == nullptr)
	{
		if(TitleWidgetClass)
		{
			TitleWidget = CreateWidget<UUserWidget>(GetWorld(), TitleWidgetClass);
		}
	}
	if(TitleWidget)
	{
		TitleWidget->AddToViewport();
	}
}

void AAnimalIslandGameMode::Restart()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FName CurrentLevelName = FName(World->GetMapName());
		UGameplayStatics::OpenLevel(World, CurrentLevelName);
	}
}

// Convert UI
void AAnimalIslandGameMode::ViewTutorialUI()
{
	if(TutorialWidget == nullptr)
	{
		if(TutorialWidgetClass)
		{
			TutorialWidget = CreateWidget<UUserWidget>(GetWorld(), TutorialWidgetClass);
			if(TutorialWidget)
			{
				if(TitleWidget)
				{
					TitleWidget->RemoveFromParent();
				}
				TutorialWidget->AddToViewport();
			}
		}
	}
	else
	{
		if(TitleWidget)
		{
			TitleWidget->RemoveFromParent();
		}
		TutorialWidget->AddToViewport();
	}
}

void AAnimalIslandGameMode::StartMainUI()
{
	if(MainWidget == nullptr)
	{
		if(MainWidgetClass)
		{
			MainWidget = CreateWidget<UMainMenu>(GetWorld(), MainWidgetClass);
			if(MainWidget)
			{
				// 마우스 위치 들어가게 할 필요
				APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				if(PlayerController)
				{
					FInputModeDataBase* InputMode = static_cast<FInputModeDataBase*>(new FInputModeGameOnly());
					PlayerController->SetInputMode(*InputMode);
					PlayerController->SetPause(false);
				}
			
				if(TutorialWidget)
				{
					TutorialWidget->RemoveFromParent();
				}
				MainWidget->AddToViewport();
			}
		}
	}
	else
	{
		if(TutorialWidget)
		{
			TutorialWidget->RemoveFromParent();
		}
		MainWidget->AddToViewport();
	}
}

void AAnimalIslandGameMode::ViewSettingUI()
{
	if(SettingWidget == nullptr)
	{
		if(SettingWidgetClass)
		{
			SettingWidget = CreateWidget<UUserWidget>(GetWorld(), SettingWidgetClass);
			if(SettingWidget)
			{
				// 마우스 위치 해제 필요
				APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				if(PlayerController)
				{
					FInputModeDataBase* InputMode = static_cast<FInputModeDataBase*>(new FInputModeUIOnly());
					PlayerController->SetInputMode(*InputMode);
				}
				if(MainWidget)
				{
					MainWidget->RemoveFromParent();
				}
				SettingWidget->AddToViewport();
			}
		}
	}
	else
	{
		if(MainWidget)
		{
			MainWidget->RemoveFromParent();
		}
		SettingWidget->AddToViewport();
	}
}

void AAnimalIslandGameMode::ViewGameoverUI()
{
	if(GameoverWidget == nullptr)
	{
		if(GameoverWidgetClass)
		{
			GameoverWidget = CreateWidget<UUserWidget>(GetWorld(), GameoverWidgetClass);
			if(GameoverWidget)
			{
				// 마우스 위치 해제 필요
				APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				if(PlayerController)
				{
					FInputModeDataBase* InputMode = static_cast<FInputModeDataBase*>(new FInputModeUIOnly());
					PlayerController->SetInputMode(*InputMode);
				}
				if(MainWidget)
				{
					MainWidget->RemoveFromParent();
				}
				GameoverWidget->AddToViewport();
			}
		}
	}
	else
	{
		if(MainWidget)
		{
			MainWidget->RemoveFromParent();
		}
		GameoverWidget->AddToViewport();
	}
}

void AAnimalIslandGameMode::SettingToMainUI()
{
	if(MainWidget == nullptr)
	{
		if(MainWidgetClass)
		{
			MainWidget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
			if(MainWidget)
			{
				// 마우스 위치 해제 필요
				APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				if(PlayerController)
				{
					FInputModeDataBase* InputMode = static_cast<FInputModeDataBase*>(new FInputModeGameOnly());
					PlayerController->SetInputMode(*InputMode);
				}
				if(SettingWidget)
				{
					SettingWidget->RemoveFromParent();
				}
				MainWidget->AddToViewport();
			}
		}
	}
	else
	{
		if(SettingWidget)
		{
			SettingWidget->RemoveFromParent();
		}
		MainWidget->AddToViewport();
	}
	
}

void AAnimalIslandGameMode::SettingToTitleUI()
{
	if(TitleWidget == nullptr)
	{
		if(TitleWidgetClass)
		{
			TitleWidget = CreateWidget<UUserWidget>(GetWorld(), TitleWidgetClass);
			if(TitleWidget)
			{
				if(SettingWidget)
				{
					SettingWidget->RemoveFromParent();
				}
				TitleWidget->AddToViewport();
			}
		}
	}
	else
	{
		if(SettingWidget)
		{
			SettingWidget->RemoveFromParent();
		}
		TitleWidget->AddToViewport();
	}
}

void AAnimalIslandGameMode::GameoverToTitleUI()
{
	if(TitleWidget == nullptr)
	{
		if(TitleWidgetClass)
		{
			TitleWidget = CreateWidget<UUserWidget>(GetWorld(), TitleWidgetClass);
			if(TitleWidget)
			{
				if(GameoverWidget)
				{
					GameoverWidget->RemoveFromParent();
				}
				TitleWidget->AddToViewport();
			}
		}
	}
	else
	{
		if(GameoverWidget)
		{
			GameoverWidget->RemoveFromParent();
		}
		TitleWidget->AddToViewport();
	}
}
