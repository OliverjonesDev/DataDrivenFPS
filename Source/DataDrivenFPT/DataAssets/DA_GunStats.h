// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_GunStats.generated.h"

/**
 * 
 */
//Inspired by Destiny's ammo system.
UENUM(BlueprintType)
enum EAmmoType
{
	Normal,Special,Heavy
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
	TEnumAsByte<EAmmoType> AmmoType;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	float FireRate;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	float ReloadRate;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	USoundBase* ReloadSound;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	USoundBase* FireSound;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	UAnimMontage* FireAnimation;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Gunplay")
	FVector MuzzleOffset;
};
