#include "STargetDummy.h"

#include "SAttributeComponent.h"

ASTargetDummy::ASTargetDummy()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	RootComponent = StaticMeshComp;

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComp"));
	AttributeComp->OnHealthChanged.AddDynamic(this, &ASTargetDummy::OnHealthChanged);
}

void ASTargetDummy::BeginPlay()
{
	Super::BeginPlay();
}

void ASTargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASTargetDummy::OnHealthChanged(AActor* ChangeInstigator, USAttributeComponent* OwningComponent, float Delta,
	float NewHealth)
{
	if (Delta < 0.0f)
	{
		StaticMeshComp->SetScalarParameterValueOnMaterials(TEXT("TimeToHit"), GetWorld()->GetTimeSeconds());	
	}
}