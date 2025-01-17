// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AnimalIslandCharacter.generated.h"


UCLASS(config=Game)
class AAnimalIslandCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Feed Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FeedAction;

	UPROPERTY(EditAnywhere, Category = Animation)
	TObjectPtr<class UAnimMontage> ThrowMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TObjectPtr<class USoundCue> DyingSound;

public:
	AAnimalIslandCharacter();
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Feed();

	UFUNCTION()
	void Damaged(int InDamage);

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditDefaultsOnly, Category = Status)
	int Hp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> FeedBPClass;

	UPROPERTY(BlueprintReadOnly ,EditDefaultsOnly, Category = Cooltime)
	float FeedCooltime;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Cooltime)
	float FeedCooltimeCnt;

	UPROPERTY()
	uint8 bIsFeedCool : 1;

	UPROPERTY()
	uint8 bSpeedUp : 1;

	UPROPERTY(BlueprintReadWrite)
	uint8 bIsEasy : 1;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UCharacterHUD> PlayerHUD;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Cooltime)
	float SpeedItemTime;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Cooltime)
	float SpeedItemTimeCnt;

	UPROPERTY()
	uint8 bCoolTimeBuf : 1;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Cooltime)
	float CoolItemTime;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Cooltime)
	float CoolItemTimeCnt;

	void CheckIsDead();

	UFUNCTION()
	void GetHealItem();

	UPROPERTY(BlueprintReadWrite)
	float MouseSensitivity;

	UPROPERTY(BlueprintReadWrite)
	float Score;
};

