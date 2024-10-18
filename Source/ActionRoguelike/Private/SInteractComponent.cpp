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
	
	GetWorld()->LineTraceSingleByObjectType(Hit, EyesLocation, EndLocation, ObjectQueryParams);
	DrawDebugLine(GetWorld(), EyesLocation, EndLocation, FColor::Red, false, 5.0, 0, 2.0);

	if (AActor* HitActor = Hit.GetActor())
	{
		DrawDebugSphere(GetWorld(), HitActor->GetActorLocation(), 10.0, 20, FColor::Red, false, 2.0, 0, 0);
		if (!HitActor->Implements<USInteractInterface>())
		{
			UE_LOG(LogTemp, Warning, TEXT("doesn't implement interact comp"));
			return;
		}

		if (APawn* PlayerPawn = Cast<APawn>(GetOwner()))
		{
			DrawDebugSphere(GetWorld(), HitActor->GetActorLocation(), 20.0, 20, FColor::Green, false, 2.0, 0, 0);
			ISInteractInterface::Execute_Interact(HitActor, PlayerPawn);
		}
	}
}

