#include "CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

ACharacterBase::ACharacterBase()
{
	bReplicates = true;
	ACharacter::SetReplicateMovement(true);

	// Network movement setup
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	ApplyMovementSpeed();
}

void ACharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACharacterBase, bIsSprinting);
	DOREPLIFETIME(ACharacterBase, bIsCrouching);
}

void ACharacterBase::ApplyMovementSpeed() const
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (!MovementComponent) return;

	float TargetSpeed = bIsCrouching ? CrouchSpeed : (bIsSprinting ? SprintSpeed : WalkSpeed);
	MovementComponent->MaxWalkSpeed = TargetSpeed;
	MovementComponent->MaxWalkSpeedCrouched = CrouchSpeed;
}

void ACharacterBase::OnRep_MovementStateChanged()
{
	ApplyMovementSpeed();
}

void ACharacterBase::HandleMoveInput(const FVector2D& MoveAxis)
{
	if (!Controller) return;

	const FRotator YawRot(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, MoveAxis.Y);
	AddMovementInput(Right, MoveAxis.X);
}

void ACharacterBase::HandleLookInput(const FVector2D& LookAxis)
{
	AddControllerYawInput(LookAxis.X);
	AddControllerPitchInput(LookAxis.Y);
}

void ACharacterBase::HandleJumpPressed()
{
	Jump();
}

void ACharacterBase::HandleJumpReleased()
{
	StopJumping();
}

void ACharacterBase::StartSprint()
{
	ServerSetSprinting(true);
}

void ACharacterBase::StopSprint()
{
	ServerSetSprinting(false);
}

void ACharacterBase::ToggleCrouch()
{
	ServerSetCrouching(!bIsCrouching);
}

void ACharacterBase::ServerSetSprinting_Implementation(bool bNewSprinting)
{
	if (bIsCrouching && bNewSprinting)
	{
		bNewSprinting = false;
	}

	bIsSprinting = bNewSprinting;
	ApplyMovementSpeed();
}

void ACharacterBase::ServerSetCrouching_Implementation(bool bNewCrouching)
{
	bIsCrouching = bNewCrouching;

	if (bIsCrouching)
	{
		Crouch();
		bIsSprinting = false;
	}
	else
	{
		UnCrouch();
	}

	ApplyMovementSpeed();
}
