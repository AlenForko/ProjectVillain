
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectVillain/Interfaces/Interactable.h"
#include "InteractionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTVILLAIN_API UInteractionComponent : public UActorComponent, public IInteractable
{
	GENERATED_BODY()

public:
	
	UInteractionComponent();
	
	void TryInteract();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
			FActorComponentTickFunction* ThisTickFunction) override;
protected:
	
	UFUNCTION(Server, reliable)
	void ServerInteract(AActor* Target);
	
	AActor* FindInteractableTarget();
	
	UPROPERTY()
	AActor* CurrentInteractableTarget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Interact")
	float InteractRange = 250.0f;
};
