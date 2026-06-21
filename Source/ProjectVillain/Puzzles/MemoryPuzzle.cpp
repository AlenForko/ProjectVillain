#include "MemoryPuzzle.h"
 
AMemoryPuzzle::AMemoryPuzzle()
{
	PrimaryActorTick.bCanEverTick = false;
	
	PuzzleDifficulty = EPuzzleDifficulty::Easy;
}

void AMemoryPuzzle::BeginPlay()
{
	Super::BeginPlay();

	TArray<UStaticMeshComponent*> Meshes;
	GetComponents<UStaticMeshComponent>(Meshes);

	for (UStaticMeshComponent* Mesh : Meshes)
	{
		if (Mesh->ComponentHasTag("Button"))
		{
			Buttons.Add(Mesh);
		}
	}
	
	StartMemoryPuzzle();
}

void AMemoryPuzzle::StartMemoryPuzzle()
{
	// Save sequence beforehand
	SaveTargetSequence();

	CurrentSequenceIndex = 0;
	GetWorldTimerManager().SetTimer(MemoryGameTimerHandle, this, &AMemoryPuzzle::PlaySequence, SequenceStartDelay, false);
}

void AMemoryPuzzle::SaveTargetSequence()
{
	if (!TargetSequence.IsEmpty())
		return;
	
	for (int32 i = 0; i < SequenceLength; i++)
	{
		if (Buttons.IsEmpty())
		{
			UE_LOG(LogTemp, Warning, TEXT("Buttons array is empty."));
			break;
		}
		
		int32 randButton = FMath::RandRange(0, Buttons.Num() - 1);
		TargetSequence.Add(randButton); 
	}

	FString SequenceString;

	for (int32 Value : TargetSequence)
	{
		SequenceString += FString::Printf(TEXT("%d "), Value);
	}

	UE_LOG(LogTemp, Warning, TEXT("Sequence is: %s"), *SequenceString);
}

void AMemoryPuzzle::PlaySequence()
{
	if (Buttons.IsEmpty() || TargetSequence.IsEmpty())
	{
		return;
	}

	if (!TargetSequence.IsValidIndex(CurrentSequenceIndex))
	{
		bIsPlayingSequence = false;
		CurrentSequenceIndex = INDEX_NONE;
		return;
	}

	bIsPlayingSequence = true;

	const int32 ButtonIndex = TargetSequence[CurrentSequenceIndex];
	if (!Buttons.IsValidIndex(ButtonIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Sequence button index %d is invalid."), ButtonIndex);
		bIsPlayingSequence = false;
		CurrentSequenceIndex = INDEX_NONE;
		return;
	}

	Buttons[ButtonIndex]->SetScalarParameterValueOnMaterials(TEXT("Glow"), 1.f);

	GetWorldTimerManager().SetTimer(
		MemoryGameTimerHandle,
		FTimerDelegate::CreateWeakLambda(this, [this, ButtonIndex]()
		{
			if (!Buttons.IsValidIndex(ButtonIndex))
			{
				bIsPlayingSequence = false;
				CurrentSequenceIndex = INDEX_NONE;
				return;
			}

			Buttons[ButtonIndex]->SetScalarParameterValueOnMaterials(TEXT("Glow"), 0.f);
			++CurrentSequenceIndex;

			if (CurrentSequenceIndex < TargetSequence.Num())
			{
				GetWorldTimerManager().SetTimer(MemoryGameTimerHandle, this, &AMemoryPuzzle::PlaySequence, SequenceStepCooldown, false);
				return;
			}

			bIsPlayingSequence = false;
			CurrentSequenceIndex = INDEX_NONE;
		}),
		GlowDuration,
		false
	);
}
