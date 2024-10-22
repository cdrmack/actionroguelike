#include "SProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ASProjectile::ASProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionProfileName("Projectile"); // created inside the editor, Project Settings -> Collision
	RootComponent = SphereComp;

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->InitialSpeed = 8000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	ParticleComp->SetupAttachment(SphereComp);
}

void ASProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ASProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentHit.AddDynamic(this, &ASProjectile::OnActorHit);
}

void ASProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void ASProjectile::Explode_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
	Destroy();
}
