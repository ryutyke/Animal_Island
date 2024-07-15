// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GJGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALISLAND_API UGJGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UGJGameInstance();

	UPROPERTY(BlueprintReadWrite)
	float SFXVolume;
	UPROPERTY(BlueprintReadWrite)
	float BGMVolume;
	UPROPERTY(BlueprintReadWrite)
	float BestScore;

	UPROPERTY(BlueprintReadWrite)
	float BestScoreEasy;

	UPROPERTY(BlueprintReadWrite)
	uint8 bIsEasy : 1;

	void BestScoreUpdate(float InScore);
	void BestScoreUpdateEasy(float InScore);
};
