#include "InteractionComponent.h"
#include "ProjectVillain/Interfaces/Interactable.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.1f;
	SetIsReplicatedByDefault(true);
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!IsValid(OwnerPawn) || !OwnerPawn->IsLocallyControlled())
	{
		return;
	}
	
	AActor* TargetActor = FindInteractableTarget();
	if (TargetActor != CurrentInteractableTarget)
	{
		CurrentInteractableTarget = TargetActor;
		
		// TODO: UI stuff here.
	}
}

void UInteractionComponent::TryInteract()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!IsValid(OwnerPawn) || !OwnerPawn->IsLocallyControlled()) return;
	
	if (!CurrentInteractableTarget) return;

	ServerInteract(CurrentInteractableTarget);
}

void UInteractionComponent::ServerInteract_Implementation(AActor* Target)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn || !Target) return;

	const float DistSq = FVector::DistSquared(
		OwnerPawn->GetActorLocation(),
		Target->GetActorLocation()
	);

	if (DistSq > FMath::Square(InteractRange + 50.f))
	{
		return;
	}

	if (Target->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		Execute_Interact(Target, OwnerPawn);
	}
}

AActor* UInteractionComponent::FindInteractableTarget()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!IsValid(OwnerPawn) || !OwnerPawn->IsLocallyControlled())
	{
		return nullptr;
	}

	if (!OwnerPawn->Controller)
	{
		return nullptr;
	}

	FVector StartLocation;
	FRotator Rotation;

	OwnerPawn->Controller->GetPlayerViewPoint(StartLocation, Rotation);

	const FVector EndPoint = StartLocation + Rotation.Vector() * InteractRange;

	FHitResult Result;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(OwnerPawn);

	const bool bHit = GetWorld()->LineTraceSingleByChannel(
		Result,
		StartLocation,
		EndPoint,
		ECC_Visibility,
		CollisionParams
	);

	if (!bHit)
	{
		return nullptr;
	}

	AActor* HitActor = Result.GetActor();

	if (HitActor && HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		return HitActor;
	}

	return nullptr;
}
