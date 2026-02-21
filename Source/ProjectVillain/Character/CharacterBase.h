#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PROJECTVILLAIN_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Movement settings
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float WalkSpeed = 450.f;

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float SprintSpeed = 650.f;

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float CrouchSpeed = 250.f;

	// Replicated movement state
	UPROPERTY(ReplicatedUsing=OnRep_IsSprinting, BlueprintReadOnly, Category="Movement")
	bool bIsSprinting = false;

	UPROPERTY(ReplicatedUsing=OnRep_IsCrouchingCustom, BlueprintReadOnly, Category="Movement")
	bool bIsCrouchingCustom = false;

	UFUNCTION()
	void OnRep_IsSprinting();

	UFUNCTION()
	void OnRep_IsCrouchingCustom();

	void ApplyMovementSpeed();
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
public:
	// Input handlers
	UFUNCTION(BlueprintCallable, Category="Movement")
	void StartSprint();

	UFUNCTION(BlueprintCallable, Category="Movement")
	void StopSprint();

	UFUNCTION(BlueprintCallable, Category="Movement")
	void ToggleCrouch();

protected:
	// Server RPCs
	UFUNCTION(Server, Reliable)
	void ServerSetSprinting(bool bNewSprinting);

	UFUNCTION(Server, Reliable)
	void ServerSetCrouching(bool bNewCrouching);
};
