#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UParticleSystem;

UCLASS(ABSTRACT) // marks this class as incomplete, helps Unreal Editor
class ACTIONROGUELIKE_API ASProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASProjectile();
	
protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Callable - allow to be called from child classes (blueprints)
	// NativeEvent - base implementation in C++, can be extended in blueprints
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<USphereComponent> SphereComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UParticleSystemComponent> ParticleComp;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UParticleSystem> ImpactVFX;
};
