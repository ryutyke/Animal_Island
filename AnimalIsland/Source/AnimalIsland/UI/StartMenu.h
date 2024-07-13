// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenu.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALISLAND_API UStartMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UStartMenu(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> StartBtn;
	
	UFUNCTION()
	void ClickedGameStart();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> SettingBtn;
	
};
