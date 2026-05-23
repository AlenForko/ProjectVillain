#pragma once

#include "CoreMinimal.h"
#include "ProjectVillain/Rooms/Room.h"
#include "PuzzleRoom.generated.h"

class USphereComponent;

UCLASS()
class PROJECTVILLAIN_API APuzzleRoom : public ARoom
{
	GENERATED_BODY()

public:
	APuzzleRoom();
	
	bool CanRoomBeSpawnedInBounds(ERoomType InRoomType, int AmountOfRoomsAllowed);
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereBounds;
};