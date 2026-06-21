#include "Puzzle.h"

#include "Net/UnrealNetwork.h"
#include "ProjectVillain/Core/ProjectVillainGameState.h"
#include "ProjectVillain/Core/ProjectVillainPlayerState.h"

APuzzle::APuzzle()
{
	bReplicates = true;
}

void APuzzle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APuzzle, PuzzleStage);
	DOREPLIFETIME(APuzzle, SolvedByPlayer);
}

void APuzzle::StartPuzzle(APlayerController* Player)
{
	if (HasAuthority())
	{
		TrySetPuzzleStage(EPuzzleStage::InProgress, Player);
	}
	else
	{
		ServerStartPuzzle(Player);
	}
}

void APuzzle::ServerStartPuzzle_Implementation(APlayerController* Player)
{
	TrySetPuzzleStage(EPuzzleStage::InProgress, Player);
}

void APuzzle::CompletePuzzle(APlayerController* Player)
{
	if (HasAuthority())
	{
		TrySetPuzzleStage(EPuzzleStage::Solved, Player);
	}
	else
	{
		ServerCompletePuzzle(Player);
	}
}

void APuzzle::ServerCompletePuzzle_Implementation(APlayerController* Player)
{
	TrySetPuzzleStage(EPuzzleStage::Solved, Player);
}

bool APuzzle::CanPlayerUsePuzzle(APlayerController* Player) const
{
	if (IsSolved())
	{
		return false;
	}

	if (!Player)
	{
		return false;
	}

	const AProjectVillainPlayerState* PlayerState = Player->GetPlayerState<AProjectVillainPlayerState>();
	if (!PlayerState || PlayerState->GetPlayerRole() != EPlayerRole::Survivor)
	{
		return false;
	}

	const AProjectVillainGameState* GameState = GetWorld() ? GetWorld()->GetGameState<AProjectVillainGameState>() : nullptr;
	if (!GameState || GameState->GetMatchPhase() != EMatchPhase::Playing)
	{
		return false;
	}

	const APawn* Pawn = Player->GetPawn();
	if (!Pawn)
	{
		return false;
	}

	const float Distance = FVector::Dist(Pawn->GetActorLocation(), GetActorLocation());
	return Distance <= InteractionDistance;
}

void APuzzle::OnPuzzleFail() const
{
	// Maybe update UI
}

bool APuzzle::TrySetPuzzleStage(EPuzzleStage NewStage, APlayerController* Player)
{
	if (!CanPlayerUsePuzzle(Player) || NewStage == EPuzzleStage::Inactive)
	{
		return false;
	}

	if (NewStage == EPuzzleStage::InProgress && PuzzleStage != EPuzzleStage::Inactive)
	{
		return false;
	}

	if (NewStage == EPuzzleStage::Solved && PuzzleStage == EPuzzleStage::Solved)
	{
		return false;
	}

	PuzzleStage = NewStage;
	SolvedByPlayer = NewStage == EPuzzleStage::Solved && Player ? Player->PlayerState : nullptr;
	return true;
}
