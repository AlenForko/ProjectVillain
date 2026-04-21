#include "DungeonGenerator.h"

#include "DungeonGeneratorConfig.h"
#include "Components/ArrowComponent.h"
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
	ARoom* MainRoom = Cast<ARoom>(GetWorld()->SpawnActor(Config->MainRoomClass.LoadSynchronous(), &FTransform::Identity));
	for (UArrowComponent* Arrow : MainRoom->GetAllSocketArrows_ServerOnly())
	{
		AvailableSpawnPoints.Add(Arrow);
	}
	if (MainRoom == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn main room"));
		Server_SpawnDungeon();
	}
	else
	{
		Config->Seed = FMath::Rand();
		AmountOfRoomsToSpawn = FMath::RandRange(Config->MinRooms, Config->MaxRooms);
		
		for (RoomsSpawned = 0; RoomsSpawned <= AmountOfRoomsToSpawn; RoomsSpawned++)
		{
			SelectNextRoom();
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Dungeon spawned with seed %d"), Config->Seed);
	UE_LOG(LogTemp, Warning, TEXT("Spawned %d rooms"), SpawnedRooms.Num());
	UE_LOG(LogTemp, Warning, TEXT("Dungeon generation complete"));
}

void ADungeonGenerator::SelectNextRoom() 
{
	const ERoomType NextRoomType = Config->SelectNextRoomType();
	TSubclassOf<ARoom> RoomSpawnClass;
	
	switch (NextRoomType)
	{
		case ERoomType::Normal:
			RoomSpawnClass = Config->NormalRoomClasses[FMath::RandRange(0, Config->NormalRoomClasses.Num() - 1)].LoadSynchronous();
			SpawnRoom(RoomSpawnClass);
			break;
		
		case ERoomType::Puzzle:
			RoomSpawnClass = Config->PuzzleRoomClasses[FMath::RandRange(0, Config->PuzzleRoomClasses.Num() - 1)].LoadSynchronous();
			SpawnRoom(RoomSpawnClass);
			break;
		
		case ERoomType::Corridor:
			RoomSpawnClass = Config->CorridorClasses[FMath::RandRange(0, Config->CorridorClasses.Num() - 1)].LoadSynchronous();
			SpawnRoom(RoomSpawnClass);
			break;
		
		case ERoomType::Hazardous:
			// TODO: Fix this later when hazardous rooms are going to be added into the game.
			RoomSpawnClass = Config->HazardousRoomClasses[FMath::RandRange(0, Config->HazardousRoomClasses.Num() - 1)].LoadSynchronous();
			SpawnRoom(RoomSpawnClass);
			break;
		
		default:
			UE_LOG(LogTemp, Warning, TEXT("Unknown room type"));
			break;
	}
}

void ADungeonGenerator::SpawnRoom(TSubclassOf<ARoom> RoomClass) 
{
	if (RoomClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid room class"));
		return;
	}
	
	ARoom* RoomSpawned = Cast<ARoom>(GetWorld()->SpawnActor(RoomClass));
	if (RoomSpawned == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn room"));
		return;
	}
	
	UArrowComponent* ChosenArrow = GetARandomSpawnPoint();
	FTransform SpawnTransform = ChosenArrow->GetComponentTransform();
	
	RoomSpawned->SetActorLocationAndRotation(SpawnTransform.GetLocation(), SpawnTransform.GetRotation().Rotator());

	UE_LOG(LogTemp, Warning, TEXT("Spawned room of type %s"), *RoomClass->GetName());
	if (RoomSpawned->IsRoomColliding())
	{
		UE_LOG(LogTemp, Warning, TEXT("Room collision detected, destroying room"));	
		RoomSpawned->Destroy();
		RoomsSpawned--;
		return;
	}
	
	for (UArrowComponent* Arrow : RoomSpawned->GetAllSocketArrows_ServerOnly())
	{
		AvailableSpawnPoints.Add(Arrow);
	}

	AvailableSpawnPoints.Remove(ChosenArrow);
	SpawnedRooms.Add(RoomSpawned);
}