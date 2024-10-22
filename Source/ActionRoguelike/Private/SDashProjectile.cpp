#include "SDashProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ASDashProjectile::ASDashProjectile()
{
	ProjectileMovementComp->InitialSpeed = 6000.0f;
}

void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DetonateTimerHandle, this, &ASDashProjectile::Explode, DetonateDelay);
}

// void ASDashProjectile::PostInitializeComponents()
// {
// 	Super::PostInitializeComponents();
//
// 	SphereComp->OnComponentHit.AddDynamic(this, &ASDashProjectile::OnActorHit);
// }

void ASDashProjectile::Explode_Implementation()
{
	// disabled since ASProjectile::Explode_Implementation destroys actor
	// Super::Explode_Implementation();

	GetWorldTimerManager().ClearTimer(DetonateTimerHandle);
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
	
	ParticleComp->DeactivateSystem();
	ProjectileMovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TeleportTimerHandle;
	GetWorldTimerManager().SetTimer(TeleportTimerHandle, this, &ASDashProjectile::DashTeleport, DashTeleportDelay);
}

void ASDashProjectile::DashTeleport() const
{
	AActor* ActorToTeleport = GetInstigator();
	ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation());
}
