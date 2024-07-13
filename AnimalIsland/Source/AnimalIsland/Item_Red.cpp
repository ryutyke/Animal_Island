// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Red.h"
#include "AnimalIslandCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AItem_Red::AItem_Red()
{
	static ConstructorHelpers::FObjectFinder<USoundCue> EatenSoundObject(TEXT("/Script/Engine.SoundCue'/Game/Assets/SFX/Ate_RedItem_Cue.Ate_RedItem_Cue'"));
	if (nullptr != EatenSoundObject.Object)
	{
		EatenSound = EatenSoundObject.Object;
	}
}

void AItem_Red::ApplyEffect()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr)
	{
		AAnimalIslandCharacter* HitCharacter = Cast<AAnimalIslandCharacter>(PlayerController->GetPawn());

		if (HitCharacter != nullptr)
		{
			Super::ApplyEffect();
			HitCharacter->GetHealItem();
		}
	}

	

}
