#include "DungeonGenerator.h"

#include "DungeonGeneratorConfig.h"
#include "ProjectVillain/Dungeon/Room.h"

ADungeonGenerator::ADungeonGenerator()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void ADungeonGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		Server_SpawnDungeon();
	}
}

void ADungeonGenerator::Server_SpawnDungeon_Implementation()
{
	AActor* MainRoom = GetWorld()->SpawnActor(Config->MainRoomClass.LoadSynchronous(), &FTransform::Identity);
	if (MainRoom == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn main room"));
		Server_SpawnDungeon();
	}
	else
	{
		Config->Seed = FMath::Rand();
		int AmountOfRoomsToSpawn = FMath::RandRange(Config->MinRooms, Config->MaxRooms);
		
		for (int i = 0; i < AmountOfRoomsToSpawn; i++)
		{
			AActor* RoomSpawned = GetWorld()->SpawnActor(ARoom::StaticClass(), &FTransform::Identity);
			if (RoomSpawned == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to spawn room"));
				return;
			}
			
			SpawnedRooms.Add(Cast<ARoom>(RoomSpawned));
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Dungeon spawned with seed %d"), Config->Seed);
	UE_LOG(LogTemp, Warning, TEXT("Spawned %d rooms"), SpawnedRooms.Num());
	UE_LOG(LogTemp, Warning, TEXT("Dungeon generation complete"));
}

void ADungeonGenerator::SelectNextRoom(ERoomType RoomType) const
{
	TSubclassOf<ARoom> RoomSpawnClass;
	
	switch (RoomType)
	{
		case ERoomType::Normal:
			// Spawn normal room
			RoomSpawnClass = Config->NormalRoomClasses[FMath::RandRange(0, Config->NormalRoomClasses.Num() - 1)].LoadSynchronous();
			SpawnRoom(RoomSpawnClass);
			break;
		case ERoomType::Puzzle:
			// Spawn puzzle room
			break;
		case ERoomType::Corridor:
			// Spawn corridor
			break;
		case ERoomType::Hazardous:
			// Spawn hazardous room
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Unknown room type"));
			break;
	}
}

void ADungeonGenerator::SpawnRoom(TSubclassOf<ARoom> RoomClass) const
{
	
}
