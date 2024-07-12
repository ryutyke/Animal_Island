// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AnimalIslandCharacter.h"

// Sets default values
AAnimal::AAnimal()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComp");
	RootComponent = SkeletalMesh;
	SkeletalMesh->SetCollisionProfileName("NoCollision");

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>("SphereComp");
	CollisionComponent->InitCapsuleSize(20.f, 60.f);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Animal"));
	CollisionComponent->SetupAttachment(RootComponent);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAnimal::OnBeginOverlap);

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

	CurrentHp = 100;
	bIsFed = false;

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

	MoveToTarget(DeltaTime);

}



bool AAnimal::OnFed()
{
	if (GetCurrentState() == EAnimalState::Hit)
	{
		return false;
	}

	SetState(EAnimalState::Hit);

	bIsFed = true;
	TargetVector.X = -TargetVector.X;
	TargetVector.Y = -TargetVector.Y;
	AddActorWorldRotation(FRotator(0.0f, 180.f, 0.f));

	return true;
	// 표정 바뀌는 거
	// 뒤 돌아보는 거
	// 뒤로 가는 거
	// 
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

void AAnimal::CheckIsDead()
{
	if (CurrentHp <= 0)
	{
		SetState(EAnimalState::Dead);
		UE_LOG(LogTemp, Log, TEXT("Animal Die"));
		Destroy();
	}
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
	if (GetCurrentState() == EAnimalState::Idle)
	{
		if ((OtherActor != this) && (OtherActor != nullptr))
		{
			AAnimalIslandCharacter* HitCharacter = Cast<AAnimalIslandCharacter>(OtherActor);
			if (HitCharacter != nullptr)
			{
				int Damage = (this->CurrentHp >= HitCharacter->Hp) ? HitCharacter->Hp : this->CurrentHp;
				//UE_LOG(LogTemp, Log, TEXT("Damage : %d"), Damage);
				this->CurrentHp -= Damage;
				HitCharacter->Hp -= Damage;
				HitCharacter->CheckIsDead();
				this->CheckIsDead();
			}
		}
	}

	else if (GetCurrentState() == EAnimalState::Hit)
	{
		if ((OtherActor != this) && (OtherActor != nullptr))
		{
			AAnimal* HitAnimal = Cast<AAnimal>(OtherActor);
			if (HitAnimal != nullptr)
			{
				//데미지 계산
				int Damage = (this->CurrentHp >= HitAnimal->CurrentHp) ? HitAnimal->CurrentHp : this->CurrentHp;
				this->CurrentHp -= Damage;
				HitAnimal->CurrentHp -= Damage;
				HitAnimal->CheckIsDead();
				this->CheckIsDead();
			}
		}
	}
	
}
