#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.generated.h"

UENUM()
enum class EPuzzleDifficulty : uint8
{
	Easy,
	Medium,
	Hard,
	Extreme
};

UENUM()
enum class EPuzzleStage : uint8
{
	Inactive,
	InProgress,
	Solved
};

UCLASS(Abstract)
class PROJECTVILLAIN_API APuzzle : public AActor
{
	GENERATED_BODY()

public:
	APuzzle();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void StartPuzzle(APlayerController* Player);

	void CompletePuzzle(APlayerController* Player);

	UFUNCTION(Server, Reliable)
	void ServerStartPuzzle(APlayerController* Player);

	UFUNCTION(Server, Reliable)
	void ServerCompletePuzzle(APlayerController* Player);

	EPuzzleStage GetPuzzleStage() const { return PuzzleStage; }

	bool IsSolved() const { return PuzzleStage == EPuzzleStage::Solved; }

protected:

	UPROPERTY(EditDefaultsOnly, Replicated, Category="Puzzle")
	EPuzzleStage PuzzleStage = EPuzzleStage::Inactive;

	UPROPERTY(EditDefaultsOnly, Category="Puzzle")
	EPuzzleDifficulty PuzzleDifficulty = EPuzzleDifficulty::Easy;

	UPROPERTY(VisibleDefaultsOnly ,Replicated, Category="Puzzle")
	APlayerState* SolvedByPlayer = nullptr;

	UPROPERTY(EditAnywhere, Category="Puzzle")
	float InteractionDistance = 300.f;

	virtual bool CanPlayerUsePuzzle(APlayerController* Player) const;

	virtual void OnPuzzleFail() const;
	bool TrySetPuzzleStage(EPuzzleStage NewStage, APlayerController* Player);
};
