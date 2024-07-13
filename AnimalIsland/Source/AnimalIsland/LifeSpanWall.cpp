// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeSpanWall.h"
#include "Components/StaticMeshComponent.h"
#include "AnimalIslandCharacter.h"

// Sets default values
ALifeSpanWall::ALifeSpanWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetWorldScale3D(FVector(40.f, 40.f, 40.f));
	RootComponent = MeshComp;

	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &ALifeSpanWall::OnBeginOverlap);

}

// Called when the game starts or when spawned
void ALifeSpanWall::BeginPlay()
{
	Super::BeginPlay();
	
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
		AAnimalIslandCharacter* HitCharacter = Cast<AAnimalIslandCharacter>(OtherActor);
		if (HitCharacter != nullptr)
		{
			// 게임오버
		}

		else
		{
			Destroy();
			// visibility 없애고 setlifespan해서 안정적으로 만들어도
		}
	}

}

