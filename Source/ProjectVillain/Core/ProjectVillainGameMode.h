#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectVillainGameMode.generated.h"

class ADungeonGenerator;
/**
 * 
 */
UCLASS()
class PROJECTVILLAIN_API AProjectVillainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AProjectVillainGameMode();
	
	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;
	virtual void BeginPlay() override;
	
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> SurvivorPawnClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> VillainPawnClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADungeonGenerator> DungeonGeneratorClass;
private:
	bool bVillainAssigned = false;
};
