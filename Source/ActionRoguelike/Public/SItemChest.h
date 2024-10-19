#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SInteractInterface.h"
#include "SItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ASItemChest : public AActor, public ISInteractInterface
{
	GENERATED_BODY()
	
public:	
	ASItemChest();

	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(APawn* InteractInstigator) override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> LidMeshComp;

	UPROPERTY(VisibleAnywhere)
	float LidTargetPitch;
	
protected:
	virtual void BeginPlay() override;
};
