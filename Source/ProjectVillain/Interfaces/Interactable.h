#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTVILLAIN_API IInteractable
{
	GENERATED_BODY()

public:
	virtual void Interact(APawn* Interactor) = 0;
};
