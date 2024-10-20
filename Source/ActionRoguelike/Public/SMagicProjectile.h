#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class UParticleSystemComponent;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASMagicProjectile();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UParticleSystemComponent> ParticleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComp;

protected:
	virtual void BeginPlay() override;
};
