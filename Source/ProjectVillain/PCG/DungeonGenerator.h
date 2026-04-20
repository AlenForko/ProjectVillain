#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.generated.h"

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
	UFUNCTION(Server, Reliable)
	void Server_SpawnDungeon();
	
	void SelectNextRoom(ERoomType RoomType) const;
	
	void SpawnRoom(TSubclassOf<ARoom> RoomClass) const;
	
	UPROPERTY(EditDefaultsOnly)
	UDungeonGeneratorConfig* Config;
	
	UPROPERTY(VisibleAnywhere)
	TArray<ARoom*> SpawnedRooms;
};
