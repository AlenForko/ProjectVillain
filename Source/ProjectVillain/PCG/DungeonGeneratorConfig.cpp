#include "DungeonGeneratorConfig.h"

void UDungeonGeneratorConfig::CheckRoomDistance(ERoomType RoomType)
{
	// If there's a puzzle room spawned X amount of spaces away, SelectNextRoomType().
}

ERoomType UDungeonGeneratorConfig::SelectNextRoomType() const
{
	// TODO: Remove puzzle rooms from the weight system and make it spawn X amount regardless with different rules.
	
	float TotalWeight = NormalRoomSpawnWeight + CorridorRoomSpawnWeight + HazardousRoomSpawnWeight + PuzzleRoomSpawnWeight;
	float Rand = FMath::FRandRange(1.f, TotalWeight);
	
	if (Rand <= NormalRoomSpawnWeight)
		return ERoomType::Normal;

	if (Rand <= NormalRoomSpawnWeight + CorridorRoomSpawnWeight)
		return ERoomType::Corridor;

	if (Rand <= NormalRoomSpawnWeight + CorridorRoomSpawnWeight + HazardousRoomSpawnWeight)
		return ERoomType::Hazardous;

	if (Rand <= TotalWeight)
		return ERoomType::Puzzle;

	return ERoomType::Normal;
}
