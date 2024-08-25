// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class UDA_GunStats;
class ADataDrivenFPTCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DATADRIVENFPT_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	
	/** Projectile class to spawn */
	UPROPERTY(EditAnywhere, Category=Projectile)
	TSubclassOf<class ADataDrivenFPTProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, Replicated)
	UDA_GunStats* GunConfig;
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/** Sets default values for this component's properties */
	UTP_WeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	bool AttachWeapon(ADataDrivenFPTCharacter* TargetCharacter);
	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	float GetAmmo()
	{
		return Ammo;
	}
	
protected:
	void AttemptToFire(APlayerController* PlayerController, UWorld* World, FVector SpawnLocation, FRotator SpawnRotation);
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UPROPERTY(VisibleAnywhere,Replicated)
	float Ammo = 0;
	UPROPERTY(VisibleAnywhere,Replicated)
	float Magazines = 4;
	

private:
	/** The Character holding this weapon*/
	ADataDrivenFPTCharacter* Character;
	FName SocketToAttachTo = TEXT("gun_hand_r");;
};
