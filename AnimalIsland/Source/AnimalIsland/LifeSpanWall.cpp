// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeSpanWall.h"
#include "Components/StaticMeshComponent.h"
#include "AnimalIslandCharacter.h"
#include "Animal.h"
#include "AnimalIslandGameMode.h"
#include "GJGameInstance.h"
#include "Feed.h"

// Sets default values
ALifeSpanWall::ALifeSpanWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetWorldScale3D(FVector(59.f, 59.f, 40.f));
	//MeshComp->BodyInstance.SetCollisionProfileName(TEXT("EdgeWall"));

	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &ALifeSpanWall::OnBeginOverlap);

}

// Called when the game starts or when spawned
void ALifeSpanWall::BeginPlay()
{
	Super::BeginPlay();
	MeshComp->BodyInstance.SetCollisionProfileName(TEXT("EdgeWall"));
}

// Called every frame
void ALifeSpanWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALifeSpanWall::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != this) && (OtherActor != nullptr))
	{
		//AAnimalIslandCharacter* HitCharacter = Cast<AAnimalIslandCharacter>(OtherActor);
		//if (HitCharacter != nullptr)
		//{
		//	// 게임오버
		//	UE_LOG(LogTemp, Warning, TEXT("Character Wall"));
		//	Cast<UGJGameInstance>(GetGameInstance())->BestScoreUpdate(HitCharacter->Score);
		//	AAnimalIslandGameMode* GameMode = Cast<AAnimalIslandGameMode>(GetWorld()->GetAuthGameMode());
		//	if (GameMode)
		//	{
		//		GameMode->ViewGameoverUI();
		//	}
		//	Cast<APlayerController>(HitCharacter->GetController())->SetPause(true);
		//}

		AAnimal* HitAnimal = Cast<AAnimal>(OtherActor);
		if (HitAnimal != nullptr)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Animal Destroy"));
			HitAnimal->Destroy();
		}
		AFeed* HitFeed = Cast<AFeed>(OtherActor);
		if (HitFeed != nullptr)
		{
			HitFeed->Destroy();
		}
	}

}

