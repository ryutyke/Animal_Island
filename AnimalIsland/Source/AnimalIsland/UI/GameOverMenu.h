// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverMenu.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALISLAND_API UGameOverMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UGameOverMenu(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> BackBtn;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> RestartBtn;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> MinuteTxt;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SecondTxt;
    
    UFUNCTION()
	void ClickedBackBtn();
	
	UFUNCTION()
	void ClickedRestartBtn();
};
