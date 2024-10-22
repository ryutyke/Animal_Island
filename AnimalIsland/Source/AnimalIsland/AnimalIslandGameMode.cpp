// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimalIslandGameMode.h"
#include "AnimalIslandCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UI/CharacterHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/MainMenu.h"
#include "UI/SettingMenu.h"
#include "UI/GameOverMenu.h"
#include "Sound/SoundCue.h"
#include "GJGameInstance.h"

AAnimalIslandGameMode::AAnimalIslandGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_Character"));
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
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
	static ConstructorHelpers::FClassFinder<UGameOverMenu> GameoverWidgetEasyRef(TEXT("/Game/UI/WB_GameOverMenuEasy.WB_GameOverMenuEasy_C"));
	if (GameoverWidgetEasyRef.Class)
	{
		GameoverWidgetEasyClass = GameoverWidgetEasyRef.Class;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> BgmSoundObject(TEXT("/Script/Engine.SoundCue'/Game/Assets/SFX/Bgm_Cue.Bgm_Cue'"));
	if (nullptr != BgmSoundObject.Object)
	{
		BgmSound = BgmSoundObject.Object;
	}

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetupAttachment(RootComponent);
}

void AAnimalIslandGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (BgmSound)
	{
		AudioComponent->SetSound(BgmSound);
		AudioComponent->Play();
	}
	
	// UI Mode
	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(PlayerController)
	{
		FInputModeDataBase* InputMode = static_cast<FInputModeDataBase*>(new FInputModeGameOnly());
		PlayerController->SetInputMode(*InputMode);
		PlayerController->bShowMouseCursor = false;
	}

	// Load All Widget
	if(MainWidgetClass)
	{
		MainWidget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
		if(MainWidget)
		{
			MainWidget->AddToViewport();
		}
	}
	if(SettingWidgetClass)
	{
		SettingWidget = CreateWidget<UUserWidget>(GetWorld(), SettingWidgetClass);
		if(SettingWidget)
		{
			SettingWidget->AddToViewport();
			SettingWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if(GameoverWidgetClass)
	{
		GameoverWidget = CreateWidget<UUserWidget>(GetWorld(), GameoverWidgetClass);
		if(GameoverWidget)
		{
			GameoverWidget->AddToViewport();
			GameoverWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (GameoverWidgetEasyClass)
	{
		GameoverWidgetEasy = CreateWidget<UUserWidget>(GetWorld(), GameoverWidgetEasyClass);
		if (GameoverWidgetEasy)
		{
			GameoverWidgetEasy->AddToViewport();
			GameoverWidgetEasy->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	AudioComponent->SetVolumeMultiplier(Cast<UGJGameInstance>(GetGameInstance())->BGMVolume);
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

void AAnimalIslandGameMode::ViewSettingUI()
{
	if(IsValid(SettingWidget) && IsValid(MainWidget))
	{
		// 마우스 위치 해제 필요
		APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if(PlayerController)
		{
			FInputModeDataBase* InputMode = static_cast<FInputModeDataBase*>(new FInputModeUIOnly());
			PlayerController->SetInputMode(*InputMode);
			PlayerController->bShowMouseCursor = true;

			PlayerController->SetPause(true);
			AAnimalIslandCharacter* Character = Cast<AAnimalIslandCharacter>(PlayerController->GetPawn());
			if(Character && Character->PlayerHUD)
			{
				Character->PlayerHUD->SetVisibility(ESlateVisibility::Hidden);
			}
		}

		MainWidget->SetVisibility(ESlateVisibility::Hidden);
		SettingWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AAnimalIslandGameMode::ViewGameoverUI()
{
	
	if(IsValid(GameoverWidget) && IsValid(MainWidget))
	{
		// 마우스 위치 해제 필요
		APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if(PlayerController)
		{
			FInputModeDataBase* InputMode = static_cast<FInputModeDataBase*>(new FInputModeUIOnly());
			PlayerController->SetInputMode(*InputMode);
			PlayerController->bShowMouseCursor = true;

			PlayerController->SetPause(true);
			AAnimalIslandCharacter* Character = Cast<AAnimalIslandCharacter>(PlayerController->GetPawn());
			if(Character && Character->PlayerHUD)
			{
				Character->PlayerHUD->SetVisibility(ESlateVisibility::Hidden);
			}
		}

		MainWidget->SetVisibility(ESlateVisibility::Hidden);
		
		if (Cast<UGJGameInstance>(GetGameInstance())->bIsEasy)
		{
			GameoverWidgetEasy->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			GameoverWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AAnimalIslandGameMode::SettingToMainUI()
{
	if(IsValid(SettingWidget) && IsValid(MainWidget))
	{
		// 마우스 위치 해제 필요
		APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if(PlayerController)
		{
			FInputModeDataBase* InputMode = static_cast<FInputModeDataBase*>(new FInputModeGameOnly());
			PlayerController->SetInputMode(*InputMode);
			PlayerController->bShowMouseCursor = false;

			PlayerController->SetPause(false);
			AAnimalIslandCharacter* Character = Cast<AAnimalIslandCharacter>(PlayerController->GetPawn());
			if(Character && Character->PlayerHUD)
			{
				Character->PlayerHUD->SetVisibility(ESlateVisibility::Visible);
			}
		}

		MainWidget->SetVisibility(ESlateVisibility::Visible);
		SettingWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AAnimalIslandGameMode::SettingToTitleUI()
{
	UGameplayStatics::OpenLevel(this, FName("Title"));
}

void AAnimalIslandGameMode::GameoverToTitleUI()
{
	UGameplayStatics::OpenLevel(this, FName("Title"));
}

void AAnimalIslandGameMode::GameoverToMainUI()
{
	Restart();
}
