#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class PROJECTVILLAIN_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

	void HandleMoveInput(const FVector2D& MoveAxis);
	
	void HandleLookInput(const FVector2D& LookAxis);
	
	void HandleJumpPressed();
	
	void HandleJumpReleased();
	
	void StartSprint();
	
	void StopSprint();
	
	void ToggleCrouch();

	bool IsSprinting() const { return bIsSprinting; }
	
	bool IsCrouching() const { return bIsCrouching; }

protected:
	virtual void BeginPlay() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_MovementStateChanged();
	
	void ApplyMovementSpeed() const;

	UFUNCTION(Server, Reliable)
	void ServerSetSprinting(bool bNewSprinting);
	
	UFUNCTION(Server, Reliable)
	void ServerSetCrouching(bool bNewCrouching);

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float WalkSpeed = 450.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float SprintSpeed = 650.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float CrouchSpeed = 250.f;
	
	UPROPERTY(ReplicatedUsing=OnRep_MovementStateChanged, BlueprintReadOnly, Category="Movement")
	bool bIsSprinting = false;
	
	UPROPERTY(ReplicatedUsing=OnRep_MovementStateChanged, BlueprintReadOnly, Category="Movement")
	bool bIsCrouching = false;
};