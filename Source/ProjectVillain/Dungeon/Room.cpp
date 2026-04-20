#include "Room.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

ARoom::ARoom()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Root);
}

void ARoom::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

TArray<UArrowComponent*> ARoom::GetAllSocketArrows_ServerOnly() const
{
	if (!HasAuthority())
		return {};

	TArray<UArrowComponent*> Result;
	GetComponents(Result);
	return Result;
}

bool ARoom::IsRoomColliding() const
{
	TArray<AActor*> OverlappingActors;
	Collision->GetOverlappingActors(OverlappingActors);
	return OverlappingActors.Num() > 0;
}
