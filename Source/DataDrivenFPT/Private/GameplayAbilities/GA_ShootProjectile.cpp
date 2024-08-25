// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/GA_ShootProjectile.h"

#include "Camera/CameraComponent.h"
#include "Characters/DataDrivenFPTCharacter.h"
#include "DataDrivenFPT/DataAssets/DA_GunStats.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Projectiles/DataDrivenFPTProjectile.h"

UGA_ShootProjectile::UGA_ShootProjectile()
{
}

void UGA_ShootProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if(HasAuthorityOrPredictionKey(ActorInfo,&ActivationInfo))
	{
		if (!CommitAbility(Handle,ActorInfo, ActivationInfo))
		{
			EndAbility(Handle,ActorInfo,ActivationInfo,true,true);
		}
	}
	OwningCharacter = Cast<ADataDrivenFPTCharacter>(ActorInfo->OwnerActor);
	GunData = OwningCharacter->GetEquippedWeapon();

	if (HasAuthority(&ActivationInfo))
	{
		if (OwningCharacter->GetEquippedWeapon()->GetAmmo() >= 0)
		{
			const FRotator SpawnRotation = OwningCharacter->GetCameraRotation();
			UE_LOG(LogTemp,Log,TEXT("Rotation : %s" ),*SpawnRotation.ToCompactString());
			const FVector SpawnLocation = OwningCharacter->GetEquippedWeapon()->GetSocketLocation("Muzzle");
			ADataDrivenFPTProjectile* New = GetWorld()->SpawnActor<ADataDrivenFPTProjectile>(OwningCharacter->GetEquippedWeapon()->ProjectileClass, SpawnLocation,SpawnRotation);
			New->SetProjectileDamage(OwningCharacter->GetEquippedWeapon()->GunConfig->DamagePerProjectile);
		}	
	}
	else
	{
		BlueprintFunctionality();
	}
	
	EndAbility(Handle,ActorInfo,ActivationInfo,true,true);
	
}




bool UGA_ShootProjectile::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                             const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UGA_ShootProjectile::InputPressed(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void UGA_ShootProjectile::CancelAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}
