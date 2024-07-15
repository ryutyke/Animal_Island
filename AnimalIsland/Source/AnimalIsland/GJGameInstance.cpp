// Fill out your copyright notice in the Description page of Project Settings.


#include "GJGameInstance.h"

UGJGameInstance::UGJGameInstance()
{
	SFXVolume = 1.0f;
	BGMVolume = 1.0f;
	BestScore = 0.f;
	BestScoreEasy = 0.f;
	bIsEasy = false;

}

void UGJGameInstance::BestScoreUpdate(float InScore)
{
	if (BestScore < InScore)
	{
		BestScore = InScore;
	}
}

void UGJGameInstance::BestScoreUpdateEasy(float InScore)
{
	if (BestScoreEasy < InScore)
	{
		BestScoreEasy = InScore;
	}
}
