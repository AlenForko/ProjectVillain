#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectVillain/Dungeon/Room.h"
#include "DungeonGeneratorConfig.generated.h"

/**
 * 
 */
class ARoom;

UCLASS(BlueprintType)
class PROJECTVILLAIN_API UDungeonGeneratorConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Rooms")
	TSoftClassPtr<ARoom> MainRoomClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Rooms")
	TArray<TSoftClassPtr<ARoom>> NormalRoomClasses;
	
	UPROPERTY(EditDefaultsOnly, Category = "Rooms")
	TArray<TSoftClassPtr<ARoom>> PuzzleRoomClasses;
	
	UPROPERTY(EditDefaultsOnly, Category = "Rooms")
	TArray<TSoftClassPtr<ARoom>> CorridorClasses;
	
	UPROPERTY(EditDefaultsOnly, Category = "Rooms")
	TArray<TSoftClassPtr<ARoom>> HazardousRoomClasses;
	
	UPROPERTY(EditAnywhere, meta=(ClampMin=0), Category = "Generation Config")
	int32 MinRooms = 5;
	
	UPROPERTY(EditAnywhere, meta=(ClampMin=0), Category = "Generation Config")
	int32 MaxRooms = 10;
	
	UPROPERTY(EditAnywhere, meta=(ClampMin=0), Category = "Generation Config")
	int32 MinPuzzleRooms = 5;
	
	UPROPERTY(EditAnywhere, meta=(ClampMin=0), Category = "Generation Config")
	int32 MaxPuzzleRooms = 10;
	
	UPROPERTY(EditAnywhere, Category = "Generation Config")
	int32 Seed = 12345;
	
	ERoomType SelectNextRoomType() const;
	
	UPROPERTY(EditAnywhere, Category = "Generation Config")
	FVector GenerationBounds = FVector(1000.0f, 1000.0f, 100.0f);
private:

	UPROPERTY(EditAnywhere, Category = "SpawnChances")
	float NormalRoomSpawnWeight;
	
	UPROPERTY(EditAnywhere, Category = "SpawnChances")
	float CorridorRoomSpawnWeight;
	
	UPROPERTY(EditAnywhere, Category = "SpawnChances")
	float HazardousRoomSpawnWeight;
	
	UPROPERTY(EditAnywhere, Category = "SpawnChances")
	float PuzzleRoomSpawnWeight;
	
	static void CheckRoomDistance(ERoomType RoomType);
};
