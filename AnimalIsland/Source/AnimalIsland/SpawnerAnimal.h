// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerAnimal.generated.h"

UCLASS()
class ANIMALISLAND_API ASpawnerAnimal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerAnimal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	float SpawnRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duration")
	float SpawnDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duration")
	float DecrementStep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Duration")
	float MinimumDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<class AAnimal> SpawnSubject;

private:
	UPROPERTY()
	FVector PlayerPosition;

	UPROPERTY()
	float SpawnDurationCnt;

	void Spawn();

	FVector CalculateRandomInCirclePosition() const;
	
	void SpawnActorAtLocation(const FVector& InLocation, const FRotator& InRotation);
};
