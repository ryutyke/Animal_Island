// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerAnimal.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnerAnimal::ASpawnerAnimal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnRange = 2000.0f;

	SpawnDuration = 3.5f;
	SpawnDurationCnt = SpawnDuration;

	DecrementStep = 0.1f;
	MinimumDuration = 1.5f;

	/*static ConstructorHelpers::FClassFinder<AActor> AnimalBPClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_Animal.BP_Animal_C'"));
	if (AnimalBPClassRef.Class)
	{
		ToSpawnAnimalClass = AnimalBPClassRef.Class;
	}*/

	static ConstructorHelpers::FClassFinder<AActor> HedgehogClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_Hedgehog.BP_Hedgehog_C'"));
	if (HedgehogClassRef.Class)
	{
		HedgehogClass = HedgehogClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<AActor> GoatClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_Goat.BP_Goat_C'"));
	if (GoatClassRef.Class)
	{
		GoatClass = GoatClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<AActor> KangarooClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_Kangaroo.BP_Kangaroo_C'"));
	if (KangarooClassRef.Class)
	{
		KangarooClass = KangarooClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<AActor> WolfClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_Wolf.BP_Wolf_C'"));
	if (WolfClassRef.Class)
	{
		WolfClass = WolfClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<AActor> TigerClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_Tiger.BP_Tiger_C'"));
	if (TigerClassRef.Class)
	{
		TigerClass = TigerClassRef.Class;
	}

	SpawnNum = 10;
	SpawnCnt = 0;

}

// Called when the game starts or when spawned
void ASpawnerAnimal::BeginPlay()
{
	Super::BeginPlay();

	// Set Target Position Once
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (PlayerController->GetPawn())
	{
		PlayerPosition = PlayerController->GetPawn()->GetActorLocation();
	}
}

// Called every frame
void ASpawnerAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnDurationCnt -= DeltaTime;
	
	if (SpawnDurationCnt <= 0.0f)
	{
		Spawn();

		// Decrease Duration Until Minimum
		SpawnDuration -= DecrementStep;
		if (SpawnDuration <= MinimumDuration)
		{
			SpawnDuration = MinimumDuration;
		}
		SpawnDurationCnt = SpawnDuration;
	}
}

void ASpawnerAnimal::Spawn()
{
	for (int i = 0; i < SpawnNum; i++)
	{
		SpawnActorAtLocation(CalculateRandomInCirclePosition(), GetActorRotation());
	}
	SpawnCnt++;
	if (SpawnCnt % 5 == 0)
	{
		SpawnNum++;
	}
}

FVector ASpawnerAnimal::CalculateRandomInCirclePosition() const
{
    float RandomAngle = FMath::RandRange(0.0f, 360.0f);
    float RandomRadius = FMath::RandRange(0.0f, 200.f);
    RandomRadius += SpawnRange;
    
    float Radian = FMath::DegreesToRadians(RandomAngle);
    
    float RandX = PlayerPosition.X + RandomRadius * FMath::Cos(Radian);
    float RandY = PlayerPosition.Y + RandomRadius * FMath::Sin(Radian);
    float RandZ = 0.f;
    //float RandZ = PlayerPosition.Z;
    
	return FVector(RandX, RandY, RandZ);
}

void ASpawnerAnimal::SpawnActorAtLocation(const FVector& InLocation, const FRotator& InRotation)
{
	TSubclassOf<AActor> ToSpawnClass;
	int RandValue = FMath::RandRange(1, 100);
	if (RandValue <= 40)
	{
		ToSpawnClass = HedgehogClass;
	}
	else if (RandValue <= 70)
	{
		ToSpawnClass = GoatClass;
	}
	else if (RandValue <= 85)
	{
		ToSpawnClass = KangarooClass;
	}
	else if (RandValue <= 95)
	{
		ToSpawnClass = WolfClass;
	}
	else
	{
		ToSpawnClass = TigerClass;
	}

    if (ToSpawnClass)
    {
        UWorld* World = GetWorld();

        if (World)
        {
            AActor* SpawnedActor = World->SpawnActor<AActor>(ToSpawnClass, InLocation, InRotation);
            if (SpawnedActor)
            {
                // Success
				float Distance = FVector::Dist(GetActorLocation(), InLocation);
				//UE_LOG(LogTemp, Warning, TEXT("Success to spawn actor. Distance: %f"), Distance);
            }
            else
            {
                //UE_LOG(LogTemp, Error, TEXT("Failed to spawn actor."));
            }
        }
    }
    else
    {
        //UE_LOG(LogTemp, Error, TEXT("ActorToSpawn is not set."));
    }
}