// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Item_Blue.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALISLAND_API AItem_Blue : public AItemBase
{
	GENERATED_BODY()
	
public:
	AItem_Blue();

	virtual void ApplyEffect() override;
};
