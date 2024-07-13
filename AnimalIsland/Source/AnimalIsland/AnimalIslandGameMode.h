// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
	TObjectPtr<UUserWidget> TitleWidget;
	TObjectPtr<UUserWidget> TutorialWidget;
	TObjectPtr<UUserWidget> MainWidget;
	TObjectPtr<UUserWidget> SettingWidget;
	TObjectPtr<UUserWidget> GameoverWidget;
private:
	UPROPERTY()
	TSubclassOf<class UStartMenu> TitleWidgetClass;
	UPROPERTY()
	TSubclassOf<class UTutorialMenu> TutorialWidgetClass;
	UPROPERTY()
	TSubclassOf<class UMainMenu> MainWidgetClass;
	UPROPERTY()
	TSubclassOf<class USettingMenu> SettingWidgetClass;
	UPROPERTY()
	TSubclassOf<class UGameOverMenu> GameoverWidgetClass;

public:
	void ViewTutorialUI();
	void StartMainUI();
	void ViewSettingUI();
	void ViewGameoverUI();
	void SettingToMainUI();
	void SettingToTitleUI();
	void GameoverToTitleUI();
};



