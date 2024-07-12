// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimalIslandCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


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
	FeedCooltime = 3.0f;
	FeedCooltimeCnt = FeedCooltime;

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
}

void AAnimalIslandCharacter::Tick(float DeltaTime)
{
	if (bIsFeedCool)
	{
		FeedCooltimeCnt -= DeltaTime;
		if (FeedCooltimeCnt <= 0)
		{
			bIsFeedCool = false;
			FeedCooltimeCnt = 0.f;
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
		GetWorld()->SpawnActor<AActor>(FeedBPClass, GetActorLocation(), GetActorRotation());
	}

}

void AAnimalIslandCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AAnimalIslandCharacter::CheckIsDead()
{
	//UE_LOG(LogTemp, Log, TEXT("%d"), Hp);
	if (Hp <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("GameOver"));
		Cast<APlayerController>(GetController())->SetPause(true);
		//Destroy();

	}
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
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

