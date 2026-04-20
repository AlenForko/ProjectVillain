#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

class UArrowComponent;

UENUM(BlueprintType)
enum class ERoomType : uint8
{
	Main,
	Normal,
	Corridor,
	Puzzle,
	Hazardous,
};

class UBoxComponent;
UCLASS()
class PROJECTVILLAIN_API ARoom : public AActor
{
	GENERATED_BODY()

public:
	ARoom();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category="Room|Sockets")
	TArray<UArrowComponent*> GetAllSocketArrows_ServerOnly() const;

	UFUNCTION(BlueprintCallable)
	bool IsRoomColliding() const;
	
	ERoomType GetRoomType() const { return RoomType; };
protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Collision;
	
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly)
	ERoomType RoomType = ERoomType::Normal;
};