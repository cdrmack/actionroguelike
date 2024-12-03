#pragma once

#include "CoreMinimal.h"
#include "SProjectile.h"
#include "SMagicProjectile.generated.h"

class UAudioComponent;
class USoundBase;

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public ASProjectile
{
	GENERATED_BODY()
public:
	ASMagicProjectile();
	
protected:
	virtual void BeginPlay() override;
	
	virtual void PostInitializeComponents() override;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UAudioComponent> AudioComp;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<USoundBase> ImpactSound;
	//TSubclassOf<USoundBase>
	
private:
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
