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

protected:
	virtual void BeginPlay() override;
};
