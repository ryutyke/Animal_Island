// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TitleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALISLAND_API ATitleGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ATitleGameMode();
	virtual void BeginPlay() override;
	
protected:
	TObjectPtr<UUserWidget> TitleWidget;
	TObjectPtr<UUserWidget> TutorialWidget;
private:
	UPROPERTY()
	TSubclassOf<class UStartMenu> TitleWidgetClass;
	UPROPERTY()
	TSubclassOf<class UTutorialMenu> TutorialWidgetClass;

public:
	void TitleToTutorial();
};
