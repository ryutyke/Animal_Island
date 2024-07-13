// Fill out your copyright notice in the Description page of Project Settings.


#include "GJGameInstance.h"

UGJGameInstance::UGJGameInstance()
{
	SFXVolume = 1.0f;
	BGMVolume = 1.0f;
	BestScore = 0.f;
}

void UGJGameInstance::BestScoreUpdate(float InScore)
{
	if (BestScore < InScore)
	{
		BestScore = InScore;
	}
}
