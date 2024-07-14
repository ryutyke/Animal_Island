// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FeedInterface.h"
#include "Animal.generated.h"

UENUM(BlueprintType)
enum class EAnimalState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Hit UMETA(DisplayName = "Hit"),
	Dead UMETA(DisplayName = "Dead")
};

UCLASS()
class ANIMALISLAND_API AAnimal : public AActor, public IFeedInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnimal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TObjectPtr<class UNiagaraComponent> NiagaraComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TObjectPtr<class UNiagaraSystem> NiagaraEffect;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	virtual bool OnFed() override;

	void UpdateIdleState(float InDeltaTime);
	void UpdateHitState();
	void UpdateDeadState();

	UFUNCTION()
	void CheckIsDead();

	UFUNCTION()
	void DropItem();

	EAnimalState GetCurrentState() { return CurrentState; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hp")
	int MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hp")
	int CurrentHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feed")
	uint8 bIsFed : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bDropItem : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> RedItemBPClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> GreenItemBPClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BlueItemBPClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<class USoundCue> FeedSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<class USoundCue> DeadSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<class USoundCue> ItemSpawnSound;
private:
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
