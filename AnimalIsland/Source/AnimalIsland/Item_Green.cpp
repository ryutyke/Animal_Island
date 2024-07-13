// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Green.h"
#include "AnimalIslandCharacter.h"
#include "Kismet/GameplayStatics.h"

AItem_Green::AItem_Green()
{
}

void AItem_Green::ApplyEffect()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr)
	{
		AAnimalIslandCharacter* HitCharacter = Cast<AAnimalIslandCharacter>(PlayerController->GetPawn());

		if (HitCharacter != nullptr)
		{
			HitCharacter->bCoolTimeBuf = true;
		}
	}
}
