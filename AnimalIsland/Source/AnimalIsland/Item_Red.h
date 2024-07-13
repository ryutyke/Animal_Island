// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Item_Red.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALISLAND_API AItem_Red : public AItemBase
{
	GENERATED_BODY()

public:
	AItem_Red();

	virtual void ApplyEffect() override;
	
};
