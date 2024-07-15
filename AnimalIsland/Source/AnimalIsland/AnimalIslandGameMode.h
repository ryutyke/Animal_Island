// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/AudioComponent.h"
#include "AnimalIslandGameMode.generated.h"

UCLASS(minimalapi)
class AAnimalIslandGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAnimalIslandGameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Restart();
	
protected:
	TObjectPtr<UUserWidget> MainWidget;
	TObjectPtr<UUserWidget> SettingWidget;
	TObjectPtr<UUserWidget> GameoverWidget;
	TObjectPtr<UUserWidget> GameoverWidgetEasy;
private:
	UPROPERTY()
	TSubclassOf<class UMainMenu> MainWidgetClass;
	UPROPERTY()
	TSubclassOf<class USettingMenu> SettingWidgetClass;
	UPROPERTY()
	TSubclassOf<class UGameOverMenu> GameoverWidgetClass;
	UPROPERTY()
	TSubclassOf<class UGameOverMenu> GameoverWidgetEasyClass;

public:
	
	
	void ViewSettingUI();
	void ViewGameoverUI();
	void SettingToMainUI();
	void SettingToTitleUI();
	void GameoverToTitleUI();
	void GameoverToMainUI();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<class USoundCue> BgmSound;

	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* AudioComponent;
};



