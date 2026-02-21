#include "SurvivorCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASurvivorCharacter::ASurvivorCharacter()
{
	WalkSpeed = 450.f;
	SprintSpeed = 650.f;
	CrouchSpeed = 250.f;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ASurvivorCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC && PC->IsLocalController())
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (PlayerMappingContext)
				{
					Subsystem->AddMappingContext(PlayerMappingContext, 0);
				}
			}
		}
	}
}

void ASurvivorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EIC) return;

	if (IA_Move) EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ASurvivorCharacter::Input_Move);
	if (IA_Look) EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ASurvivorCharacter::Input_Look);
	if (IA_Jump)
	{
		EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ASurvivorCharacter::Input_JumpPressed);
		EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ASurvivorCharacter::Input_JumpReleased);
	}
	if (IA_Sprint)
	{
		EIC->BindAction(IA_Sprint, ETriggerEvent::Started, this, &ASurvivorCharacter::Input_SprintPressed);
		EIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ASurvivorCharacter::Input_SprintReleased);
	}
	if (IA_CrouchToggle)
		EIC->BindAction(IA_CrouchToggle, ETriggerEvent::Started, this, &ASurvivorCharacter::Input_CrouchToggle);
}

void ASurvivorCharacter::Input_Move(const FInputActionValue& Value)
{
	const FVector2D Move = Value.Get<FVector2D>();
	if (!Controller) return;

	const FRotator ControlRot = Controller->GetControlRotation();
	const FRotator YawRot(0.f, ControlRot.Yaw, 0.f);

	AddMovementInput(FRotationMatrix(YawRot).GetUnitAxis(EAxis::X), Move.Y);
	AddMovementInput(FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y), Move.X);

	// Rotate character to face where the player is looking
	SetActorRotation(YawRot);
}

void ASurvivorCharacter::Input_Look(const FInputActionValue& Value)
{
	const FVector2D Look = Value.Get<FVector2D>();
	AddControllerYawInput(Look.X);
	AddControllerPitchInput(Look.Y);
}

void ASurvivorCharacter::Input_JumpPressed(const FInputActionValue&) { Jump(); }
void ASurvivorCharacter::Input_JumpReleased(const FInputActionValue&) { StopJumping(); }
void ASurvivorCharacter::Input_SprintPressed(const FInputActionValue&) { StartSprint(); }
void ASurvivorCharacter::Input_SprintReleased(const FInputActionValue&) { StopSprint(); }
void ASurvivorCharacter::Input_CrouchToggle(const FInputActionValue&) { ToggleCrouch(); }
