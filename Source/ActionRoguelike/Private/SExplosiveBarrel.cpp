#include "SExplosiveBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"

ASExplosiveBarrel::ASExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetSimulatePhysics(true);
	RootComponent = StaticMeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(StaticMeshComp);
	RadialForceComp->SetAutoActivate(false); // otherwise it slowly keeps pushing things away
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	RadialForceComp->Radius = 750.0f;
	RadialForceComp->ImpulseStrength = 2500.0f;
	RadialForceComp->bImpulseVelChange = true; // ignore mass of objects
}

void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
}

void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StaticMeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);
}

void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();
}