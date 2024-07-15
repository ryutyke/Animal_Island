// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialMenu.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALISLAND_API UTutorialMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UTutorialMenu(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> StartBtn;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> EasyBtn;

	UFUNCTION()
	void ClickedGameStart();

	UFUNCTION()
	void ClickedGameStartEasy();
};
