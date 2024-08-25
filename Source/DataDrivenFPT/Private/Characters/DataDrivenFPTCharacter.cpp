	// Copyright Epic Games, Inc. All Rights Reserved.

	#include "Characters/DataDrivenFPTCharacter.h"

	#include "AbilitySystemComponent.h"
	#include "Projectiles/DataDrivenFPTProjectile.h"
	#include "EnhancedInputComponent.h"
	#include "EnhancedInputSubsystems.h"
	#include "InputActionValue.h"
	#include "Animation/AnimInstance.h"
	#include "Camera/CameraComponent.h"
	#include "Components/CapsuleComponent.h"
	#include "Components/SkeletalMeshComponent.h"
	#include "DataDrivenFPT/DataAssets/DA_GunStats.h"
	#include "Engine/LocalPlayer.h"
	#include "Kismet/GameplayStatics.h"
	#include "Net/UnrealNetwork.h"

	DEFINE_LOG_CATEGORY(LogTemplateCharacter);

	//////////////////////////////////////////////////////////////////////////
	// ADataDrivenFPTCharacter

	ADataDrivenFPTCharacter::ADataDrivenFPTCharacter()
	{
		// Set size for collision capsule
		GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
			
		// Create a CameraComponent	
		FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
		AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
		FirstPersonCameraComponent->SetupAttachment(GetMesh(),"head");
		FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
		FirstPersonCameraComponent->bUsePawnControlRotation = true;

	}

	UAbilitySystemComponent* ADataDrivenFPTCharacter::GetAbilitySystemComponent() const
	{
		return AbilitySystemComponent;
	}

	bool ADataDrivenFPTCharacter::IsAlive()
	{
		return true;
	}

	float ADataDrivenFPTCharacter::GetHealth() const
	{
		return 0;
	}


	float ADataDrivenFPTCharacter::GetMaxHealth() const
	{
		return 0;
	}

	float ADataDrivenFPTCharacter::GetStamina() const
	{
		return 0;
	}

	float ADataDrivenFPTCharacter::GetMaxStamina() const
	{
		return 0;
	}

	float ADataDrivenFPTCharacter::GetMoveSpeed() const
	{
		return 0;
	}

	float ADataDrivenFPTCharacter::GetMoveSpeedBaseValue() const
	{
		return 0;
	}

	void ADataDrivenFPTCharacter::Die()
	{
	}

	void ADataDrivenFPTCharacter::FinishDying()
	{
	}

	void ADataDrivenFPTCharacter::SetEquippedWeapon(UTP_WeaponComponent* NewWeapon)
	{
		EquippedWeapon = NewWeapon;
	}



	void ADataDrivenFPTCharacter::AddCharacterAbilities()
	{
	}

	void ADataDrivenFPTCharacter::InitializeAttributes()
	{
	}

	void ADataDrivenFPTCharacter::AddStartupEffects()
	{
	}

	void ADataDrivenFPTCharacter::SetMana(float Mana)
	{
	}

	void ADataDrivenFPTCharacter::SetStamina(float Stamina)
	{
	}
	void ADataDrivenFPTCharacter::SetHealth(float Health)
	{
	}

	void ADataDrivenFPTCharacter::BeginPlay()
	{
		// Call the base class  
		Super::BeginPlay();
	}

	//////////////////////////////////////////////////////////////////////////// Input

	void ADataDrivenFPTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
	{	
		// Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			// Jumping
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

			// Moving
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADataDrivenFPTCharacter::Move);

			// Looking
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADataDrivenFPTCharacter::Look);

			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ADataDrivenFPTCharacter::ExecuteFireAction);
		}
		else
		{
			UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
		}
	}

	void ADataDrivenFPTCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
	{
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	}


	UTP_WeaponComponent* ADataDrivenFPTCharacter::GetEquippedWeapon()
	{
		return EquippedWeapon;
	}

	void ADataDrivenFPTCharacter::Move(const FInputActionValue& Value)
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

	void ADataDrivenFPTCharacter::Look(const FInputActionValue& Value)
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

	void ADataDrivenFPTCharacter::ExecuteFireAction(const FInputActionValue& Value)
	{
		Server_Fire();
	}

	void ADataDrivenFPTCharacter::Server_Fire_Implementation()
	{
		//Server is firing weapon using GAS, then playing animation montage via a multicast to all users.
		if (EquippedWeapon)
		{
			AbilitySystemComponent->GiveAbility(EquippedWeapon->GunConfig->GunBehaviour);
			AbilitySystemComponent->TryActivateAbilityByClass(EquippedWeapon->GunConfig->GunBehaviour);
			Multicast_Fire();
		}	
	}

	void ADataDrivenFPTCharacter::Multicast_Fire_Implementation()
	{
		if (EquippedWeapon)
		{
			PlayAnimMontage(EquippedWeapon->GunConfig->FireAnimation);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(),EquippedWeapon->GunConfig->FireSound,GetActorLocation());
		}
	}
