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

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Input Assets
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

	// Input handlers
	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);
	void Input_JumpPressed(const FInputActionValue& Value);
	void Input_JumpReleased(const FInputActionValue& Value);
	void Input_SprintPressed(const FInputActionValue& Value);
	void Input_SprintReleased(const FInputActionValue& Value);
	void Input_CrouchToggle(const FInputActionValue& Value);
};
