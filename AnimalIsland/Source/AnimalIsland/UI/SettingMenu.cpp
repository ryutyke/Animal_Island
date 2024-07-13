// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SettingMenu.h"

#include "AnimalIslandGameMode.h"
#include "Components/Button.h"
#include "Components/Image.h"

USettingMenu::USettingMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Mouse Setting
	// MouseArrows.Add(Mouse_First_Arrow);
	// MouseArrows.Add(Mouse_Second_Arrow);
	// MouseArrows.Add(Mouse_Third_Arrow);
	// MouseArrows.Add(Mouse_Fourth_Arrow);
}

void USettingMenu::NativeConstruct()
{
	Super::NativeConstruct();
	BindButtonEvent();
}

void USettingMenu::BindButtonEvent() const
{
	MouseFirstBtn->OnClicked.AddDynamic(this, &USettingMenu::ClickedMouseFirstArrow);
	MouseSecondBtn->OnClicked.AddDynamic(this, &USettingMenu::ClickedMouseSecondArrow);
	MouseThirdBtn->OnClicked.AddDynamic(this, &USettingMenu::ClickedMouseThirdArrow);
	MouseFourthBtn->OnClicked.AddDynamic(this, &USettingMenu::ClickedMouseFourthArrow);
	BackBtn->OnClicked.AddDynamic(this, &USettingMenu::ClickedBackBtn);
	ExitBtn->OnClicked.AddDynamic(this, &USettingMenu::ClickedExitBtn);
}

void USettingMenu::ClickedMouseFirstArrow()
{
	//ChangeSettingState(ESettingMenu::Mouse, 0);
	Mouse_First_Arrow->SetVisibility(ESlateVisibility::Visible);
	Mouse_Second_Arrow->SetVisibility(ESlateVisibility::Hidden);
	Mouse_Third_Arrow->SetVisibility(ESlateVisibility::Hidden);
	Mouse_Fourth_Arrow->SetVisibility(ESlateVisibility::Hidden);
}

void USettingMenu::ClickedMouseSecondArrow()
{
	//ChangeSettingState(ESettingMenu::Mouse, 1);
	Mouse_Second_Arrow->SetVisibility(ESlateVisibility::Visible);
	Mouse_First_Arrow->SetVisibility(ESlateVisibility::Hidden);
	Mouse_Third_Arrow->SetVisibility(ESlateVisibility::Hidden);
	Mouse_Fourth_Arrow->SetVisibility(ESlateVisibility::Hidden);
}

void USettingMenu::ClickedMouseThirdArrow()
{
	//ChangeSettingState(ESettingMenu::Mouse, 2);
	Mouse_Third_Arrow->SetVisibility(ESlateVisibility::Visible);
	Mouse_First_Arrow->SetVisibility(ESlateVisibility::Hidden);
	Mouse_Second_Arrow->SetVisibility(ESlateVisibility::Hidden);
	Mouse_Fourth_Arrow->SetVisibility(ESlateVisibility::Hidden);
}

void USettingMenu::ClickedMouseFourthArrow()
{
	//ChangeSettingState(ESettingMenu::Mouse, 3);
	
	Mouse_Fourth_Arrow->SetVisibility(ESlateVisibility::Visible);
	Mouse_First_Arrow->SetVisibility(ESlateVisibility::Hidden);
	Mouse_Second_Arrow->SetVisibility(ESlateVisibility::Hidden);
	Mouse_Third_Arrow->SetVisibility(ESlateVisibility::Hidden);
}

void USettingMenu::ClickedBackBtn()
{
	AAnimalIslandGameMode* GameMode = Cast<AAnimalIslandGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->SettingToMainUI();
	}
}

void USettingMenu::ClickedExitBtn()
{
	AAnimalIslandGameMode* GameMode = Cast<AAnimalIslandGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->SettingToTitleUI();
	}
}

void USettingMenu::ChangeSettingState(ESettingMenu Category, int32 InLevel)
{
	TArray<TObjectPtr<UImage>> SetCategory;
	switch(Category)
	{
	case ESettingMenu::Mouse:
		SetCategory = MouseArrows;
		break;
	default:
		SetCategory = MouseArrows;
		break;
	}
	if(SetCategory.Num()>0)
	{
		for(auto i=0; i<SetCategory.Num(); ++i)
		{
			if(i==InLevel)
			{
				SetCategory[i]->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				SetCategory[i]->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}
