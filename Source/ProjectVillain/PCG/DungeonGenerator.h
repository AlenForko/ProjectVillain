#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.generated.h"

class UArrowComponent;
enum class ERoomType : uint8;
class UDungeonGeneratorConfig;
class ARoom;

UCLASS()
class PROJECTVILLAIN_API ADungeonGenerator : public AActor
{
	GENERATED_BODY()

public:
	ADungeonGenerator();
	
protected:
	virtual void BeginPlay() override;

private:
	int AmountOfRoomsToSpawn = 0;
	int RoomsSpawned = 0;
	
	UFUNCTION(Server, Reliable)
	void Server_SpawnDungeon();
	
	void SelectNextRoom();

	void SpawnRoom(TSubclassOf<ARoom> RoomClass);
	
	TArray<UArrowComponent*> AvailableSpawnPoints;
	
	UArrowComponent* GetARandomSpawnPoint() { return AvailableSpawnPoints[FMath::RandRange(0, AvailableSpawnPoints.Num() - 1)]; }
	
	UPROPERTY(EditDefaultsOnly)
	UDungeonGeneratorConfig* Config;
	
	UPROPERTY(VisibleAnywhere)
	TArray<ARoom*> SpawnedRooms;

	// Helper function declarations
	FVector GetCenterOfBoundingBox(const FVector& Bounds);
	FVector GetRandomPositionInBounds(const FVector& Bounds);
	bool IsPositionValid(const FVector& Position, float MinDistance, const TArray<ARoom*>& ExistingRooms);
	ARoom* SpawnRoomAtPosition(TSubclassOf<ARoom> RoomClass, const FVector& Position);
};
