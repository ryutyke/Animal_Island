// Fill out your copyright notice in the Description page of Project Settings.


#include "Feed.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFeed::AFeed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;
	//SphereComp->SetCollisionProfileName("Feed");
	SphereComp->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	SphereComp->SetSphereRadius(16.0f);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	//MeshComp->SetWorldRotation(FRotator(0.0f, 90.0f, 0.0f));
	MeshComp->SetupAttachment(RootComponent);

	SphereComp->OnComponentHit.AddDynamic(this, &AFeed::OnHit);
}

// Called when the game starts or when spawned
void AFeed::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(10.0f);
}

// Called every frame
void AFeed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ForwardVector = GetActorForwardVector();
	FVector NewLocation = GetActorLocation() + (ForwardVector * Speed * DeltaTime);
	SetActorLocation(NewLocation);
}

void AFeed::OnEaten()
{

}

void AFeed::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	// if 동물이라면 ~~~ 또는 콜리전채널 써서 동물이랑만 충돌하게
	// OnEaten()
	// OtherActor 동물Base로 Cast해서 .OnFed()
}