// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Blue.h"
#include "AnimalIslandCharacter.h"
#include "Kismet/GameplayStatics.h"

AItem_Blue::AItem_Blue()
{
}

void AItem_Blue::ApplyEffect()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr)
	{
		AAnimalIslandCharacter* HitCharacter = Cast<AAnimalIslandCharacter>(PlayerController->GetPawn());

		if (HitCharacter != nullptr)
		{
			HitCharacter->bSpeedUp = true;
		}
	}
}
