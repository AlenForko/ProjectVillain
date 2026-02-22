#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/PlayerController.h"
#include "ProjectVillainPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class ACharacterBase;

UCLASS()
class PROJECTVILLAIN_API AProjectVillainPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	// Enhanced Input Assets (assign in BP defaults)
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

private:
	UPROPERTY()
	TObjectPtr<ACharacterBase> CachedBaseCharacter;

	// Input handlers
	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);
	void Input_JumpStarted(const FInputActionValue& Value);
	void Input_JumpCompleted(const FInputActionValue& Value);
	void Input_SprintStarted(const FInputActionValue& Value);
	void Input_SprintCompleted(const FInputActionValue& Value);
	void Input_CrouchToggle(const FInputActionValue& Value);

	void CachePossessedCharacter();
};
