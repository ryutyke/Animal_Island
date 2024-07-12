// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FeedInterface.h"
#include "Feed.generated.h"

UCLASS()
class ANIMALISLAND_API AFeed : public AActor, public IFeedInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFeed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class USphereComponent> SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UStaticMeshComponent> MeshComp;

	UPROPERTY(EditDefaultsOnly)
	float Speed = 2000.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnEaten() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
