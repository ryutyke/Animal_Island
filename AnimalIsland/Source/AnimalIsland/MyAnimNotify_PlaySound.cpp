// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotify_PlaySound.h"
#include "GJGameInstance.h"

void UMyAnimNotify_PlaySound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (MeshComp && MeshComp->GetWorld())
    {
        UWorld* World = MeshComp->GetWorld();
        
        //UE_LOG(LogTemp, Warning, TEXT("%f"), Cast<UGJGameInstance>(World->GetGameInstance())->SFXVolume);
        if (World->GetGameInstance())
        {
            VolumeMultiplier = Cast<UGJGameInstance>(World->GetGameInstance())->SFXVolume;
        }
    }
    Super::Notify(MeshComp, Animation, EventReference);
}
