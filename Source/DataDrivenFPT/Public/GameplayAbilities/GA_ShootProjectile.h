// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Characters/DataDrivenFPTCharacter.h"
#include "DataDrivenFPT/DataAssets/DA_GunStats.h"
#include "GA_ShootProjectile.generated.h"

/**
 * 
 */
UCLASS()
class UGA_ShootProjectile : public UGameplayAbility
{
	GENERATED_BODY()
public :
	UGA_ShootProjectile();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	UFUNCTION(BlueprintImplementableEvent)
	void BlueprintFunctionality();
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Data")
	UTP_WeaponComponent* GunData;
	UPROPERTY(BlueprintReadOnly, Category = "Data")
	ADataDrivenFPTCharacter* OwningCharacter;
};
