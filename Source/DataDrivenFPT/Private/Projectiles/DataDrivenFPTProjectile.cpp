// Copyright Epic Games, Inc. All Rights Reserved.

#include "Projectiles/DataDrivenFPTProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ADataDrivenFPTProjectile::ADataDrivenFPTProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ADataDrivenFPTProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	//set replicates for networking.
	bReplicates = true;
}

void ADataDrivenFPTProjectile::SetProjectileDamage(float newDamage)
{
	ProjectileDamage = newDamage;
}

void ADataDrivenFPTProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		if (GetLocalRole() == ROLE_Authority)
		{
			if (OtherActor->Implements<UI_Damageable>())
			{
				UE_LOG(LogClass, Log, TEXT("Server : Damage Dealt to %s : %f"), *OtherActor->GetName(),ProjectileDamage);
				Cast<II_Damageable>(OtherActor)->Execute_I_TakeDamage(OtherActor,ProjectileDamage);	
			}
		}
		Destroy();	
	}
}

