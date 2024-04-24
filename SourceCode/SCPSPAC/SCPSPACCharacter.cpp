// Copyright Epic Games, Inc. All Rights Reserved.

#include "SCPSPACCharacter.h"
#include "DoorTeleport.h"
#include "EquipmentComponent.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ASCPSPACCharacter

ASCPSPACCharacter::ASCPSPACCharacter()
{
	// Character doesnt have a rifle at start
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	if (eqComponent == nullptr)
		eqComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EQ"));

	eqComponent->MoveComp = GetCharacterMovement();
	eqComponent->Player = GetMesh1P();

	//LoadLevel();
	//eqComponent->LoadItmes();
}

void ASCPSPACCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//if(GameInstanceSave->AvailableSaving)
	//	GameInstanceSave->SavingAcessLevel(Level);

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void ASCPSPACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASCPSPACCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASCPSPACCharacter::Look);

		// Cast Ray
		EnhancedInputComponent->BindAction(ShowRay, ETriggerEvent::Triggered, this, &ASCPSPACCharacter::RayInte);

		// Select Itme
		EnhancedInputComponent->BindAction(NextItme, ETriggerEvent::Triggered, this, &ASCPSPACCharacter::NextItmeFun);

		// Use Itme
		EnhancedInputComponent->BindAction(SelectItem, ETriggerEvent::Triggered, this, &ASCPSPACCharacter::Use);

		//Loding Battery
		EnhancedInputComponent->BindAction(UseBattery, ETriggerEvent::Triggered, this, &ASCPSPACCharacter::Battery);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ASCPSPACCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ASCPSPACCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Test"));
	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASCPSPACCharacter::NextItmeFun()
{
	eqComponent->SelectItem();
}

void ASCPSPACCharacter::Battery()
{
	eqComponent->LoadingBattery();
}

void ASCPSPACCharacter::Use()
{
	FVector StartPos = FirstPersonCameraComponent->GetComponentLocation();
	FVector CamVector = FirstPersonCameraComponent->GetForwardVector();

	m_CameraLoc = StartPos + (CamVector * 75);
	eqComponent->losCamera = m_CameraLoc;
	eqComponent->UseingItem();
}

//void ASCPSPACCharacter::LoadLevel()//NOT WORKING
//{
//	Level = GameInstanceSave->LevelToLoad();
//	eqComponent->LoadItmes();
//}

void ASCPSPACCharacter::RayInte()
{
	//Set up all vector
	FHitResult hit;
	FVector StartPos = FirstPersonCameraComponent->GetComponentLocation();
	FVector CamVector = FirstPersonCameraComponent->GetForwardVector();
	// End of ray
	FVector EndRay = StartPos + (CamVector * 1250);
	GWorld->LineTraceSingleByChannel(hit, StartPos, EndRay, ECC_Visibility, FCollisionQueryParams());

	//Check if ray is being block by Actor
	if (hit.bBlockingHit == true)
	{
		//seft checks
		if (eqComponent == nullptr)
			eqComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EQ"));

		//Get Actor
		auto hitActor = hit.GetActor();
		//Check if is a Item them pick up 
		if (hitActor->ActorHasTag(TEXT("Item")))
			eqComponent->PickUPItem(hitActor);

		//Get a Item Level
		Level = eqComponent->LevelBuffor;
		//GameInstanceSave->SavingAcessLevel(Level);

		//Chek if is a door to change level by cast 
		if (ADoorTeleport* Door = Cast<ADoorTeleport>(hitActor))
		{
			bool d = Door->OpenDoor(Level);

			if (d == false)
				UE_LOG(LogTemp, Error, TEXT("Error to teleport or open the door (Level card is lower then Level acces of door)"));
		}


	}
}