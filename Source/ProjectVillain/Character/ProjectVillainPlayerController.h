#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProjectVillainPlayerController.generated.h"

class AProjectVillainHUD;
class ACharacterBase;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class PROJECTVILLAIN_API AProjectVillainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void AcknowledgePossession(APawn* P) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> PlayerMappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Sprint;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_CrouchToggle;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<AProjectVillainHUD> MainHUD;

private:
	UPROPERTY()
	TObjectPtr<ACharacterBase> CachedBaseCharacter;

	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);
	void Input_JumpStarted(const FInputActionValue& Value);
	void Input_JumpCompleted(const FInputActionValue& Value);
	void Input_SprintStarted(const FInputActionValue& Value);
	void Input_SprintCompleted(const FInputActionValue& Value);
	void Input_CrouchToggle(const FInputActionValue& Value);

	void CachePossessedCharacter(APawn* InPawn = nullptr);
	ACharacterBase* GetControlledCharacter();
};
