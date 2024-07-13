// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingMenu.generated.h"

UENUM(BlueprintType)
enum class ESettingMenu : uint8
{
	Mouse UMETA(DisplayName = "Mouse"),
	BGM UMETA(DisplayName = "BGM"),
	SFX UMETA(DisplayName = "SFX")
};


/**
 * 
 */
UCLASS()
class ANIMALISLAND_API USettingMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USettingMenu(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

private:
	void BindButtonEvent() const;
	
	// Mouse Setting Arrows
	UPROPERTY()
	TArray<TObjectPtr<class UImage>> MouseArrows; 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Mouse_First_Arrow;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> MouseFirstBtn;
	UFUNCTION()
	void ClickedMouseFirstArrow();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Mouse_Second_Arrow;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MouseSecondBtn;
	UFUNCTION()
	void ClickedMouseSecondArrow();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Mouse_Third_Arrow;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MouseThirdBtn;
	UFUNCTION()
	void ClickedMouseThirdArrow();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Mouse_Fourth_Arrow;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MouseFourthBtn;
	UFUNCTION()
	void ClickedMouseFourthArrow();

	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackBtn;
	UFUNCTION()
	void ClickedBackBtn();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitBtn;
	UFUNCTION()
	void ClickedExitBtn();

	void ChangeSettingState(ESettingMenu Category, int32 InLevel);
};
