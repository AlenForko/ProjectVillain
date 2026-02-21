#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "SurvivorCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class PROJECTVILLAIN_API ASurvivorCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	ASurvivorCharacter();
	
};
