// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ProjectVillainGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVILLAIN_API AProjectVillainGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	
	AProjectVillainGameState();

	void StartMatchTimer();
	void DecreaseTimer();
	
	float GetTimeRemaining() const { return TimeRemaining; }
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(ReplicatedUsing=OnRep_TimeRemaining, BlueprintReadOnly)
	float TimeRemaining = 600.f;
	
	UFUNCTION()
	void OnRep_TimeRemaining();
	
	FTimerHandle MatchTimerHandle;
};
