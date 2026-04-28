#include "Room.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

ARoom::ARoom()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);
	
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	Collision->SetupAttachment(Mesh);
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

bool ARoom::IsRoomColliding() 
{
	TArray<AActor*> OverlappingActors;
	Collision->GetOverlappingActors(OverlappingActors, ARoom::StaticClass());
	OverlappingActors.Remove(this);
	return OverlappingActors.Num() > 0;
}
