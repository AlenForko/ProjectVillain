// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectVillainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVILLAIN_API AProjectVillainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	AProjectVillainGameMode();

	virtual void PostLogin(APlayerController* NewPlayerController) override;
	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;
	
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> SurvivorPawnClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> VillainPawnClass;

private:
	bool bVillainAssigned = false;
};
