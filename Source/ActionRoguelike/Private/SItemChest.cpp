#include "SItemChest.h"

#include "Components/StaticMeshComponent.h"

ASItemChest::ASItemChest()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	RootComponent = BaseMeshComp;

	LidMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComp"));
	LidMeshComp->SetupAttachment(BaseMeshComp);

	LidTargetPitch = 110.0f;
}

void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
}

void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASItemChest::Interact_Implementation(APawn* InteractInstigator)
{
	LidMeshComp->SetRelativeRotation(FRotator(LidTargetPitch, 0, 0));
}

