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
	SphereComp->SetSphereRadius(24.0f);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionProfileName("NoCollision");
	MeshComp->SetWorldScale3D(FVector(0.15f, 0.15f, 0.15f));
	//MeshComp->SetWorldRotation(FRotator(0.0f, 90.0f, 0.0f));
	MeshComp->SetupAttachment(RootComponent);

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFeed::OnBeginOverlap);
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
	Destroy();
}

void AFeed::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("DDDDDDDDDDDDD"));
	if ((OtherActor != this) && (OtherActor != nullptr))
	{
		/*AFeed* FeedCheck = Cast<AFeed>(OtherActor);
		if (FeedCheck != nullptr)
		{
			return;
		}*/

		IFeedInterface* FeedInterface = Cast<IFeedInterface>(OtherActor);
		if (FeedInterface != nullptr)
		{
			if (FeedInterface->OnFed())
			{
				this->OnEaten();
			}
		}
	}
}