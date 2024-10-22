#pragma once

#include "CoreMinimal.h"
#include "SProjectile.h"
#include "SDashProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASDashProjectile : public ASProjectile
{
	GENERATED_BODY()

protected:
	ASDashProjectile();

	virtual void BeginPlay() override;

	// virtual void PostInitializeComponents() override;

	virtual void Explode_Implementation() override;

	UPROPERTY(EditAnywhere, Category="Teleport")
	float DashTeleportDelay = 0.2f;

	UPROPERTY(EditAnywhere, Category="Teleport")
	float DetonateDelay = 0.2f;

private:
	void DashTeleport() const;
	
	FTimerHandle DetonateTimerHandle;
};
