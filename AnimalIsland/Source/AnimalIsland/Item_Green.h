// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Item_Green.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALISLAND_API AItem_Green : public AItemBase
{
	GENERATED_BODY()

public:
	AItem_Green();

	virtual void ApplyEffect() override;
	
};
