// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Animal.generated.h"

UENUM(BlueprintType)
enum class EAnimalState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Hit UMETA(DisplayName = "Hit"),
	Dead UMETA(DisplayName = "Dead")
};

UCLASS()
class ANIMALISLAND_API AAnimal : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnimal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UFUNCTION()
	void OnFed();

	void UpdateIdleState(float InDeltaTime);
	void UpdateHitState();
	void UpdateDeadState();

	EAnimalState GetCurrentState() { return CurrentState; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float MoveSpeed;
	

private:
	UPROPERTY()
	TObjectPtr<class USphereComponent> CollisionComponent;

	UPROPERTY()
	TObjectPtr<class USkeletalMeshComponent> SkeletalMesh;

	UPROPERTY()
	EAnimalState CurrentState;

	UPROPERTY()
	FVector TargetVector;

	

	void SetState(EAnimalState NewState);
	void HandleState(EAnimalState InState, float InDeltaTime);

	void MoveToTarget(float InDeltaTime);

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
