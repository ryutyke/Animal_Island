// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "AnimalIslandCharacter.h"
#include "GJGameInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

// Sets default values
AAnimal::AAnimal()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComp");
	RootComponent = SkeletalMesh;
	SkeletalMesh->SetCollisionProfileName("NoCollision");

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>("SphereComp");
	CollisionComponent->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
	CollisionComponent->InitCapsuleSize(20.f, 90.f);
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

	static ConstructorHelpers::FClassFinder<AActor> RedItemBPClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_Item_Red.BP_Item_Red_C'"));
	if (RedItemBPClassRef.Class)
	{
		RedItemBPClass = RedItemBPClassRef.Class;
	}
	static ConstructorHelpers::FClassFinder<AActor> GreenItemBPClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_Item_Green.BP_Item_Green_C'"));
	if (GreenItemBPClassRef.Class)
	{
		GreenItemBPClass = GreenItemBPClassRef.Class;
	}
	static ConstructorHelpers::FClassFinder<AActor> BlueItemBPClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_Item_Blue.BP_Item_Blue_C'"));
	if (BlueItemBPClassRef.Class)
	{
		BlueItemBPClass = BlueItemBPClassRef.Class;
	}

	CurrentState = EAnimalState::Idle;
	MoveSpeed = 1000.f;

	MaxHp = 100;
	
	bIsFed = false;

	bDropItem = false;

	static ConstructorHelpers::FObjectFinder<USoundCue> FeedSoundObject(TEXT("/Script/Engine.SoundCue'/Game/Assets/SFX/AnimalAteSound_Cue.AnimalAteSound_Cue'"));
	if (nullptr != FeedSoundObject.Object)
	{
		FeedSound = FeedSoundObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> ItemSpawnSoundObject(TEXT("/Script/Engine.SoundCue'/Game/Assets/SFX/Item_Shown_Cue.Item_Shown_Cue'"));
	if (nullptr != ItemSpawnSoundObject.Object)
	{
		ItemSpawnSound = ItemSpawnSoundObject.Object;
	}

	// Effect
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraEffectRef (TEXT("/Script/Niagara.NiagaraSystem'/Game/Assets/VFX/VFX_Shine.VFX_Shine'"));
	if(NiagaraEffectRef.Object)
	{
		NiagaraEffect = NiagaraEffectRef.Object;
		//UE_LOG(LogTemp, Warning, TEXT("Succeed Loading NiagaraEffect"));
	}

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComp->SetupAttachment(RootComponent);

	NiagaraComp->SetAsset(NiagaraEffect);
	NiagaraComp->SetRelativeScale3D(FVector(1, 1, 1));
	NiagaraComp->Deactivate();
}

// Called when the game starts or when spawned
void AAnimal::BeginPlay()
{
	NiagaraComp->Deactivate();
	int temp = FMath::RandRange(0, 9);
	if (temp <= 3)
	{
		bDropItem = true;
		// Niagara
		NiagaraComp->Activate();
		UE_LOG(LogTemp, Warning, TEXT("Activate NiagaraEffect %d"), bDropItem);
	}

	Super::BeginPlay();
	CurrentHp = MaxHp;
	//SetLifeSpan(10.f);

	SetState(EAnimalState::Idle);


	// Set Target Position Once
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	int RandIntX = FMath::RandRange(-300, 300);
	int RandIntY = FMath::RandRange(-300, 300);
	FVector PlayerPos = PlayerController->GetPawn()->GetActorLocation();
	PlayerPos.Z = GetActorLocation().Z;
	PlayerPos.X += RandIntX;
	PlayerPos.Y += RandIntY;

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

	UGameplayStatics::PlaySound2D(this, FeedSound, CastChecked<UGJGameInstance>(GetWorld()->GetGameInstance())->SFXVolume);

	SetState(EAnimalState::Hit);

	bIsFed = true;

	if (bDropItem)
	{
		DropItem();
		return Destroy();
	}

	else
	{
		TargetVector.X = -TargetVector.X;
		TargetVector.Y = -TargetVector.Y;
		AddActorWorldRotation(FRotator(0.0f, 180.f, 0.f));
	}
	return true;
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
		if (DeadSound != nullptr)
		{
			UGameplayStatics::PlaySound2D(this, DeadSound, CastChecked<UGJGameInstance>(GetWorld()->GetGameInstance())->SFXVolume);
		}
		UE_LOG(LogTemp, Log, TEXT("Animal Die"));
		Destroy();
	}
}

void AAnimal::DropItem()
{
	int RandVar = FMath::RandRange(0, 9);
	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.Z = -160.0f;

	// �Ҹ�
	UGameplayStatics::PlaySound2D(this, ItemSpawnSound, CastChecked<UGJGameInstance>(GetWorld()->GetGameInstance())->SFXVolume);

	if (RandVar <= 4)
	{
		GetWorld()->SpawnActor<AActor>(BlueItemBPClass, SpawnLocation, GetActorRotation());
	}
	else if (RandVar <= 8)
	{
		GetWorld()->SpawnActor<AActor>(RedItemBPClass, SpawnLocation, GetActorRotation());
	}
	else
	{
		GetWorld()->SpawnActor<AActor>(GreenItemBPClass, SpawnLocation, GetActorRotation());
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
				HitCharacter->Damaged(Damage);
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
				//������ ���
				int Damage = (this->CurrentHp >= HitAnimal->CurrentHp) ? HitAnimal->CurrentHp : this->CurrentHp;
				this->CurrentHp -= Damage;
				HitAnimal->CurrentHp -= Damage;
				HitAnimal->CheckIsDead();
				this->CheckIsDead();
			}
		}
	}
	
}
