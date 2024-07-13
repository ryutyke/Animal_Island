// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Blue.h"
#include "AnimalIslandCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AItem_Blue::AItem_Blue()
{
	static ConstructorHelpers::FObjectFinder<USoundCue> EatenSoundObject(TEXT("/Script/Engine.SoundCue'/Game/Assets/SFX/Ate_BlueItem_Cue.Ate_BlueItem_Cue'"));
	if (nullptr != EatenSoundObject.Object)
	{
		EatenSound = EatenSoundObject.Object;
	}
}

void AItem_Blue::ApplyEffect()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr)
	{
		AAnimalIslandCharacter* HitCharacter = Cast<AAnimalIslandCharacter>(PlayerController->GetPawn());

		if (HitCharacter != nullptr)
		{
			Super::ApplyEffect();
			HitCharacter->bSpeedUp = true;
		}
	}
}
