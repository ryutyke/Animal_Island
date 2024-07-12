// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimalIslandGameMode.h"
#include "AnimalIslandCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AAnimalIslandGameMode::AAnimalIslandGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AAnimalIslandGameMode::Restart()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FName CurrentLevelName = FName(World->GetMapName());
		UGameplayStatics::OpenLevel(World, CurrentLevelName);
	}
}