#include "MemoryPuzzle.h"

AMemoryPuzzle::AMemoryPuzzle()
{
	PrimaryActorTick.bCanEverTick = false;
	
	PuzzleDifficulty = EPuzzleDifficulty::Easy;
}

void AMemoryPuzzle::BeginPlay()
{
	Super::BeginPlay();
}