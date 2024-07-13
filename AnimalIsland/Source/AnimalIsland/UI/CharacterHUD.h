// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "CharacterHUD.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALISLAND_API UCharacterHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UCharacterHUD(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_0;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_2;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_3;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_4;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_5;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_6;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_7;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_8;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_9;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_10;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_11;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_12;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_13;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_14;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_15;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_16;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_17;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_18;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> HPImg_19;

	UPROPERTY()
	TArray<TObjectPtr<class UImage>> ImageArray;

	UPROPERTY()
	int LifeCnt;

	UFUNCTION()
	void UpdateLifeImage(int InHp);

	UFUNCTION()
	void FillImageArray();
	
};
