// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Red.h"
#include "AnimalIslandCharacter.h"
#include "Kismet/GameplayStatics.h"

AItem_Red::AItem_Red()
{
	
}

void AItem_Red::ApplyEffect()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr)
	{
		AAnimalIslandCharacter* HitCharacter = Cast<AAnimalIslandCharacter>(PlayerController->GetPawn());

		if (HitCharacter != nullptr)
		{
			HitCharacter->GetHealItem();
		}
	}

	

}
