// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
AAnimal::AAnimal()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sphere Collision
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	CollisionComponent->InitSphereRadius(30.0f);
	RootComponent = CollisionComponent;

	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Animal"));
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAnimal::OnBeginOverlap);


	// Skeletal Mesh
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));
	if (SkeletalMeshRef.Object)
	{
		SkeletalMesh->SetSkeletalMesh(SkeletalMeshRef.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AAnimal: Failed to Load Skeletal Mesh"));
	}

	CurrentState = EAnimalState::Idle;
	MoveSpeed = 1000.f;

}

// Called when the game starts or when spawned
void AAnimal::BeginPlay()
{
	Super::BeginPlay();
	SetState(EAnimalState::Idle);


	// Set Target Position Once
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	int RandIntX = FMath::RandRange(-500, 500);
	int RandIntY = FMath::RandRange(-500, 500);
	FVector PlayerPos = PlayerController->GetPawn()->GetActorLocation();
	PlayerPos.Z = GetActorLocation().Z;
	PlayerPos.X += -10;
	PlayerPos.Y += -10;

	TargetVector = (PlayerPos - GetActorLocation()).GetSafeNormal();

	SetActorRotation(TargetVector.Rotation() + FRotator(0.0f, -90.f, 0.f));
}

// Called every frame
void AAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleState(CurrentState, DeltaTime);

}

// Delegate // Need Binding
void AAnimal::OnFed()
{
	SetState(EAnimalState::Hit);
}

void AAnimal::UpdateIdleState(float InDeltaTime)
{
	// Move Randomly
	MoveToTarget(InDeltaTime);
}

void AAnimal::UpdateHitState()
{
	// 
}

void AAnimal::UpdateDeadState()
{
	// 
}

void AAnimal::SetState(EAnimalState NewState)
{
	CurrentState = NewState;
	HandleState(NewState, 0.0f);
}

void AAnimal::HandleState(EAnimalState InState, float InDeltaTime)
{
	switch (InState)
	{
	case EAnimalState::Idle:
		UpdateIdleState(InDeltaTime);
		break;
	case EAnimalState::Hit:
		UpdateHitState();
		break;
	case EAnimalState::Dead:
		UpdateDeadState();
		break;
	default:
		break;
	}
}

void AAnimal::MoveToTarget(float InDeltaTime)
{
	SetActorLocation(GetActorLocation() + TargetVector * InDeltaTime * MoveSpeed);
}

void AAnimal::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != this) && (OtherActor != nullptr))
	{
		AAnimal* HitAnimal = Cast<AAnimal>(OtherActor);
		if (HitAnimal != nullptr)
		{
			if ((GetCurrentState() != EAnimalState::Idle) && (HitAnimal->GetCurrentState() == EAnimalState::Idle))
			{
				SetState(EAnimalState::Dead);
				HitAnimal->SetState(EAnimalState::Dead);
			}
		}
	}
}
