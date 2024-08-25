// Copyright Epic Games, Inc. All Rights Reserved.



#include "Components/TP_WeaponComponent.h"

#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Characters/DataDrivenFPTCharacter.h"
#include "DataDrivenFPT/DataAssets/DA_GunStats.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "Projectiles/DataDrivenFPTProjectile.h"


// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	//MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
	SetIsReplicated(true);

	if (GunConfig)
	{
		Ammo = GunConfig->MaxAmountAmmo;
	}
}

void UTP_WeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
}




bool UTP_WeaponComponent::AttachWeapon(ADataDrivenFPTCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	//Sets the owner for server authority
	GetOwner()->SetOwner(Character);
	// Check that the character is valid, and has no weapon component yet
	if (Character == nullptr || Character->GetInstanceComponents().FindItemByClass<UTP_WeaponComponent>())
	{
		return false;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh(), AttachmentRules, SocketToAttachTo);

	// add the weapon as an instance component to the character
	Character->AddInstanceComponent(this);
	Character->SetEquippedWeapon(this);

	return true;
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}