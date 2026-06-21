#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "MemoryPuzzle.generated.h"

UCLASS()
class PROJECTVILLAIN_API AMemoryPuzzle : public APuzzle
{
	GENERATED_BODY()

public:
	AMemoryPuzzle();

	void StartMemoryPuzzle();
	
protected:
	virtual void BeginPlay() override;
	
	// TODO: Just for testing purposes, remove later.
	UPROPERTY(EditAnywhere, Category="Memory Puzzle", meta=(ClampMin="0.0"))
	float SequenceStartDelay = 1.5f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Memory Puzzle | Buttons")
	TArray<UStaticMeshComponent*> Buttons;
	
	UPROPERTY(VisibleInstanceOnly, Category="Memory Puzzle")
	TArray<int32> TargetSequence;

	UPROPERTY(VisibleInstanceOnly, Category="Memory Puzzle")
	TArray<int32> PlayerSequence;
	
private:
	// SEQUENCE
	UPROPERTY(EditAnywhere, Category="Memory Puzzle|Sequence", meta=(ClampMin="1"))
	int32 SequenceLength = 6;
	
	UPROPERTY(EditDefaultsOnly, Category="MemoryPuzzle|Sequence")
	float GlowDuration = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, Category="MemoryPuzzle|Sequence")
	float SequenceStepCooldown = 0.2f;
	///////////
	
	FTimerHandle MemoryGameTimerHandle;
	
	void SaveTargetSequence();
	
	UFUNCTION()
	void PlaySequence();
	
	int32 CurrentSequenceIndex = INDEX_NONE;
	bool bIsPlayingSequence = false;
};
