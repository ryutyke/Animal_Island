// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "AnimalIslandCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;
	//SphereComp->SetCollisionProfileName("Feed");
	SphereComp->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	SphereComp->SetSphereRadius(24.0f);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetWorldScale3D(FVector(0.15f, 0.15f, 0.15f));
	//MeshComp->SetWorldRotation(FRotator(0.0f, 90.0f, 0.0f));
	MeshComp->SetupAttachment(RootComponent);

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::ApplyEffect()
{
}

void AItemBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != this) && (OtherActor != nullptr))
	{
		AAnimalIslandCharacter* HitCharacter = Cast<AAnimalIslandCharacter>(OtherActor);
		if (HitCharacter != nullptr)
		{
			ApplyEffect();
			Destroy();
		}
	}
}

