// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimalIslandCharacter.h"

#include "AnimalIslandGameMode.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "GJGameInstance.h"
#include "UI/CharacterHUD.h"


//////////////////////////////////////////////////////////////////////////
// AAnimalIslandCharacter

AAnimalIslandCharacter::AAnimalIslandCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	Hp = 100;
	bIsFeedCool = false;
	bSpeedUp = false;
	bCoolTimeBuf = false;
	FeedCooltime = 3.0f;
	FeedCooltimeCnt = 0.0f;
	SpeedItemTime = 5.0f;
	SpeedItemTimeCnt = 0;
	CoolItemTime = 3.0f;
	CoolItemTimeCnt = 0;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionFeedRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Feed.IA_Feed'"));
	if (nullptr != InputActionFeedRef.Object)
	{
		FeedAction = InputActionFeedRef.Object;
	}

	static ConstructorHelpers::FClassFinder<AActor> FeedBPClassRef(TEXT("/Script/Engine.Blueprint'/Game/Actors/BP_Feed.BP_Feed_C'"));
	if (FeedBPClassRef.Class)
	{
		FeedBPClass = FeedBPClassRef.Class;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ThrowMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Assets/Player/AM_Throw_Cut.AM_Throw_Cut'"));
	if (ThrowMontageRef.Succeeded())
	{
		ThrowMontage = ThrowMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> DyingSoundObject(TEXT("/Script/Engine.SoundCue'/Game/Assets/SFX/Character_Dying_Cue.Character_Dying_Cue'"));
	if (nullptr != DyingSoundObject.Object)
	{
		DyingSound = DyingSoundObject.Object;
	}

	MouseSensitivity = 1.f;

	Score = 0.0f;

	bIsEasy = false;
}

void AAnimalIslandCharacter::Tick(float DeltaTime)
{
	CheckIsDead();
	Score += DeltaTime;
	if (bIsFeedCool)
	{
		FeedCooltimeCnt -= DeltaTime;

		//if (bCoolTimeBuf) FeedCooltimeCnt = 0;
		
		if (FeedCooltimeCnt <= 0)
		{
			bIsFeedCool = false;
			FeedCooltimeCnt = 0.f;
		}
	}

	if (bSpeedUp)
	{
		GetCharacterMovement()->MaxWalkSpeed = 1000.f;
		SpeedItemTimeCnt -= DeltaTime;
		if (SpeedItemTimeCnt <= 0)
		{
			bSpeedUp = false;
			SpeedItemTimeCnt = 0.f;
			GetCharacterMovement()->MaxWalkSpeed = 500.f;
		}
	}

	if (bCoolTimeBuf)
	{
		// 스킬 쿨타임
		CoolItemTimeCnt -= DeltaTime;
		if (CoolItemTimeCnt <= 0)
		{
			bCoolTimeBuf = false;
			CoolItemTimeCnt = 0.f;
			
			if (bIsEasy)
			{
				FeedCooltime = 2.0f;
			}
			else
			{
				FeedCooltime = 3.0f;
			}
		}
	}
}

void AAnimalIslandCharacter::Feed()
{
	// 조준선 and 카메라 방향으로 회전 후 쏘는 거 또는 그냥 조준선 없이 캐릭터 방향으로 그대로 쏘는 거
	
	// 쿨타임
	if (!bIsFeedCool)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(ThrowMontage);
		FeedCooltimeCnt = FeedCooltime;
		bIsFeedCool = true;
		FRotator temp = GetControlRotation();
		temp.Pitch = 0.0f;
		temp.Roll = 0.0f;
		SetActorRotation(temp);

		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Z -= 30.0f;
		GetWorld()->SpawnActor<AActor>(FeedBPClass, SpawnLocation, GetActorRotation());
	}

}

void AAnimalIslandCharacter::Damaged(int InDamage)
{
	Hp -= InDamage;
	if (Hp < 0) Hp = 0;
	PlayerHUD->UpdateLifeImage(Hp);
}

void AAnimalIslandCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if(Cast<UGJGameInstance>(GetGameInstance())->bIsEasy)
	{
		bIsEasy = true;
		FeedCooltime = 2.0f;
	}

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	PlayerHUD->FillImageArray();
}

void AAnimalIslandCharacter::CheckIsDead()
{
	//UE_LOG(LogTemp, Log, TEXT("%d"), Hp);
	if (Hp <= 0 || GetActorLocation().Z < -240.f)
	{
		SetActorTickEnabled(false);
		UE_LOG(LogTemp, Log, TEXT("GameOver"));
		if (bIsEasy)
		{
			Cast<UGJGameInstance>(GetGameInstance())->BestScoreUpdateEasy(Score);
		}
		else
		{
			Cast<UGJGameInstance>(GetGameInstance())->BestScoreUpdate(Score);
		}
		UGameplayStatics::PlaySound2D(this, DyingSound, CastChecked<UGJGameInstance>(GetWorld()->GetGameInstance())->SFXVolume);
		AAnimalIslandGameMode* GameMode = Cast<AAnimalIslandGameMode>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->ViewGameoverUI();
		}
		
		Cast<APlayerController>(GetController())->SetPause(true);
		//Destroy();

	}
}

void AAnimalIslandCharacter::GetHealItem()
{
	Hp += 25;
	if (Hp > 100) Hp = 100;
	PlayerHUD->UpdateLifeImage(Hp);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAnimalIslandCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAnimalIslandCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAnimalIslandCharacter::Look);

		//Feeding
		EnhancedInputComponent->BindAction(FeedAction, ETriggerEvent::Triggered, this, &AAnimalIslandCharacter::Feed);
	}

}

void AAnimalIslandCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AAnimalIslandCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X * MouseSensitivity);
		AddControllerPitchInput(LookAxisVector.Y * MouseSensitivity);
	}
}

