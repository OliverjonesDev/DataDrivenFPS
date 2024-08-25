// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Abilities/GameplayAbility.h"
#include "DA_GunStats.generated.h"

/**
 * 
 */
//Inspired by Destiny's ammo system.
UENUM(BlueprintType)
enum EAmmoType
{
	Normal = 0,Special = 1,Heavy = 2
};
UENUM(BlueprintType)
enum EHoldType
{
	OneHanded = 0 ,TwoHanded = 1
};
UENUM(BlueprintType)
enum EWeaponType
{
	Primary = 0,Secondary = 1,Tertiary = 2
};

//Data driven gun creation 
UCLASS(BlueprintType)
class DATADRIVENFPT_API UDA_GunStats : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	USkeletalMesh* GunMesh;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	FString GunName;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	FRotator AttachmentRotation;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	FName SocketName;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	FVector MuzzleOffset;
	/**
	 * 
	 */
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	TSubclassOf<UGameplayAbility> GunBehaviour;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Ammo")
	TEnumAsByte<EAmmoType> AmmoType;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Ammo")
	float DamagePerProjectile = 10;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Ammo")
	float MaxAmountAmmo = 24;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Ammo")
	float MaxAmountMags = 24;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	TEnumAsByte<EHoldType> HoldType;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	TEnumAsByte<EWeaponType> WeaponType;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	float FireRate;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Reload")
	float ReloadRate;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Reload")
	USoundBase* ReloadSound;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Reload")
	UAnimMontage* ReloadAnimation;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	USoundBase* FireSound;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	UAnimMontage* FireAnimation;
};
