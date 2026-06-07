// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectVillainGameState.h"

#include "Net/UnrealNetwork.h"

AProjectVillainGameState::AProjectVillainGameState()
{
	bReplicates = true;
}

void AProjectVillainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AProjectVillainGameState, MatchPhase);
	DOREPLIFETIME(AProjectVillainGameState, TimeRemaining);
}

void AProjectVillainGameState::StartMatchTimer()
{
	if (HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(MatchTimerHandle, this, &AProjectVillainGameState::DecreaseTimer, 1.f, true);
	}
}

void AProjectVillainGameState::SetMatchPhase(EMatchPhase NewMatchPhase)
{
	if (!HasAuthority() || MatchPhase == NewMatchPhase)
	{
		return;
	}

	MatchPhase = NewMatchPhase;
	OnRep_MatchPhase();
}

void AProjectVillainGameState::DecreaseTimer()
{
	if (!HasAuthority()) return;
	
	TimeRemaining--;
	if (FMath::IsNearlyZero(TimeRemaining))
	{
		TimeRemaining = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(MatchTimerHandle);
		SetMatchPhase(EMatchPhase::Ended);
		
		//TODO: TRIGGER VILLAIN WIN
	}
}

void AProjectVillainGameState::OnRep_MatchPhase()
{
	// Hook for phase-driven UI and gameplay reactions.
}

void AProjectVillainGameState::OnRep_TimeRemaining()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			1.0f,
			FColor::Yellow,
			FString::Printf(TEXT("Time Remaining: %.0f"), TimeRemaining)
		);
	}
	// UPDATE UI
}
