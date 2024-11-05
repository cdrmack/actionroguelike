#include "SAttributeComponent.h"

USAttributeComponent::USAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Health = 100.0f;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool USAttributeComponent::ApplyHealthChange(float DeltaHealth)
{
	Health += DeltaHealth;

	OnHealthChanged.Broadcast(nullptr, this, DeltaHealth, Health);
	
	return true; // TODO
}

