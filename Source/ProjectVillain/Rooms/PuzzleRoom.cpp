#include "PuzzleRoom.h"

#include "Components/SphereComponent.h"

APuzzleRoom::APuzzleRoom()
{
	PrimaryActorTick.bCanEverTick = false;
	
	RoomType = ERoomType::Puzzle;
	
	SphereBounds = CreateDefaultSubobject<USphereComponent>(TEXT("SphereBounds"));
	SphereBounds->SetupAttachment(Mesh);
}

bool APuzzleRoom::CanRoomBeSpawnedInBounds(ERoomType InRoomType, int AmountOfRoomsAllowed)
{
	TArray<AActor*> OverlappingRooms;
	SphereBounds->GetOverlappingActors(OverlappingRooms, ARoom::StaticClass());
	OverlappingRooms.Remove(this);
	
	for (AActor* Actor : OverlappingRooms)
	{
		if (Cast<ARoom>(Actor)->GetRoomType() != InRoomType)
		{
			OverlappingRooms.Remove(Actor);
		}
	}
	
	if (AmountOfRoomsAllowed >= OverlappingRooms.Num())
		return false;
	
	return true;
}

void APuzzleRoom::BeginPlay()
{
	Super::BeginPlay();
	
	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereBounds->GetScaledSphereRadius(), 12, FColor::Green, true, 10.f);
}
