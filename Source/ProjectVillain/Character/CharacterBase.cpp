#include "CharacterBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"

ACharacterBase::ACharacterBase()
{
	bReplicates = true;
	SetReplicateMovement(true);

	UCharacterMovementComponent* Movement = GetCharacterMovement();
	
	Movement->NavAgentProps.bCanCrouch = true;
	bUseControllerRotationYaw = false;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
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
	DOREPLIFETIME(ACharacterBase, bIsCrouchingCustom);
}

void ACharacterBase::ApplyMovementSpeed()
{
	if (auto* Movement = GetCharacterMovement())
	{
		Movement->MaxWalkSpeed = bIsCrouchingCustom ? CrouchSpeed : (bIsSprinting ? SprintSpeed : WalkSpeed);
	}
}

void ACharacterBase::OnRep_IsSprinting()
{
	ApplyMovementSpeed();
}
void ACharacterBase::OnRep_IsCrouchingCustom()
{
	ApplyMovementSpeed();
}

void ACharacterBase::StartSprint()
{
	if (!bIsSprinting) ServerSetSprinting(true);
}

void ACharacterBase::StopSprint()
{
	if (bIsSprinting) ServerSetSprinting(false);
}

void ACharacterBase::ToggleCrouch()
{
	ServerSetCrouching(!bIsCrouchingCustom);
}

void ACharacterBase::ServerSetSprinting_Implementation(bool bNewSprinting)
{
	if (bIsCrouchingCustom && bNewSprinting) bNewSprinting = false;
	bIsSprinting = bNewSprinting;
	ApplyMovementSpeed();
}

void ACharacterBase::ServerSetCrouching_Implementation(bool bNewCrouching)
{
	bIsCrouchingCustom = bNewCrouching;
	bIsCrouchingCustom ? Crouch() : UnCrouch();
	if (bIsCrouchingCustom) bIsSprinting = false;
	ApplyMovementSpeed();
}
