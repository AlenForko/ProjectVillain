// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ProjectVillainGameState.generated.h"

UENUM()
enum class EMatchPhase : uint8
{
	WaitingToStart,
	Playing,
	Ended
};

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
	void SetMatchPhase(EMatchPhase NewMatchPhase);
	
	float GetTimeRemaining() const { return TimeRemaining; }
	EMatchPhase GetMatchPhase() const { return MatchPhase; }
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(ReplicatedUsing=OnRep_MatchPhase)
	EMatchPhase MatchPhase = EMatchPhase::WaitingToStart;

	UPROPERTY(ReplicatedUsing=OnRep_TimeRemaining, BlueprintReadOnly)
	float TimeRemaining = 600.f;

	UFUNCTION()
	void OnRep_MatchPhase();
	
	UFUNCTION()
	void OnRep_TimeRemaining();
	
	FTimerHandle MatchTimerHandle;
};
