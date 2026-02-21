#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/PlayerController.h"
#include "ProjectVillainPlayerController.generated.h"

class ACharacterBase;
UCLASS()
class PROJECTVILLAIN_API AProjectVillainPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

	TObjectPtr<ACharacterBase> BaseCharacter;
	// Input handlers
	void Input_Move(const struct FInputActionValue& Value);
	void Input_Look(const struct FInputActionValue& Value);
	void Input_JumpPressed(const struct FInputActionValue& Value);
	void Input_JumpReleased(const struct FInputActionValue& Value);
	void Input_SprintPressed(const struct FInputActionValue& Value);
	void Input_SprintReleased(const struct FInputActionValue& Value);
	void Input_CrouchToggle(const struct FInputActionValue& Value);

	// Input action references
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> PlayerMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Move;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Look;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Jump;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Sprint;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_CrouchToggle;

	virtual void BeginPlay() override;
};
