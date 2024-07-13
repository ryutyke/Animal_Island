// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterHUD.h"

UCharacterHUD::UCharacterHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	LifeCnt = 20;

	/*ImageArray.Add(HPImg_0);
	ImageArray.Add(HPImg_1);
	ImageArray.Add(HPImg_2);
	ImageArray.Add(HPImg_3);
	ImageArray.Add(HPImg_4);
	ImageArray.Add(HPImg_5);
	ImageArray.Add(HPImg_6);
	ImageArray.Add(HPImg_7);
	ImageArray.Add(HPImg_8);
	ImageArray.Add(HPImg_9);
	ImageArray.Add(HPImg_10);
	ImageArray.Add(HPImg_11);
	ImageArray.Add(HPImg_12);
	ImageArray.Add(HPImg_13);
	ImageArray.Add(HPImg_14);
	ImageArray.Add(HPImg_15);
	ImageArray.Add(HPImg_16);
	ImageArray.Add(HPImg_17);
	ImageArray.Add(HPImg_18);
	ImageArray.Add(HPImg_19);*/
}

void UCharacterHUD::UpdateLifeImage(int InHp)
{
	int NewLifeCnt = InHp / 5;

	if (NewLifeCnt > LifeCnt)
	{
		for (int i = LifeCnt; i < NewLifeCnt; i++)
		{
			ImageArray[i]->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		for (int i = NewLifeCnt; i < LifeCnt; i++)
		{
			ImageArray[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	LifeCnt = NewLifeCnt;
}

void UCharacterHUD::FillImageArray()
{
	ImageArray.Add(HPImg_0);
	ImageArray.Add(HPImg_1);
	ImageArray.Add(HPImg_2);
	ImageArray.Add(HPImg_3);
	ImageArray.Add(HPImg_4);
	ImageArray.Add(HPImg_5);
	ImageArray.Add(HPImg_6);
	ImageArray.Add(HPImg_7);
	ImageArray.Add(HPImg_8);
	ImageArray.Add(HPImg_9);
	ImageArray.Add(HPImg_10);
	ImageArray.Add(HPImg_11);
	ImageArray.Add(HPImg_12);
	ImageArray.Add(HPImg_13);
	ImageArray.Add(HPImg_14);
	ImageArray.Add(HPImg_15);
	ImageArray.Add(HPImg_16);
	ImageArray.Add(HPImg_17);
	ImageArray.Add(HPImg_18);
	ImageArray.Add(HPImg_19);
}

