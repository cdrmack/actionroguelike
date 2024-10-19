#include "SInteractComponent.h"

#include "SInteractInterface.h"
// #include "EntitySystem/MovieSceneEntitySystemRunner.h"

USInteractComponent::USInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USInteractComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USInteractComponent::PrimaryInteract()
{
	FHitResult Hit;

	FVector EyesLocation;
	FRotator EyesRotation;
	GetOwner()->GetActorEyesViewPoint(EyesLocation, EyesRotation);
	
	const FVector EndLocation = EyesLocation + (EyesRotation.Vector() * 1000);
	
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	TArray<FHitResult> HitResults;
	constexpr float SweepSphereRadius = 20.0f;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(SweepSphereRadius);
	const bool bBlockingHit = GetWorld()->SweepMultiByObjectType(HitResults, EyesLocation, EndLocation, FQuat::Identity, ObjectQueryParams, CollisionShape);

	const FColor DebugLineColor = bBlockingHit ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), EyesLocation, EndLocation, DebugLineColor, false, 2.0, 0, 2.0);
	
	for (const FHitResult& HitResult : HitResults)
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			FColor DebugSphereColor = FColor::Red;
			if (HitActor->Implements<USInteractInterface>())
			{
				DebugSphereColor = FColor::Green;
				DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, SweepSphereRadius, 20, DebugSphereColor, false, 2.0, 0, 0);
				
				if (APawn* PlayerPawn = Cast<APawn>(GetOwner()))
				{
					ISInteractInterface::Execute_Interact(HitActor, PlayerPawn);
				}
				break; // do not interact with multiple actors
			}
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, SweepSphereRadius, 20, DebugSphereColor, false, 2.0, 0, 0);
		}	
	}
}

