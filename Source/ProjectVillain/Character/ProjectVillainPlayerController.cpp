#include "ProjectVillainPlayerController.h"
#include "CharacterBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AProjectVillainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	BaseCharacter = Cast<ACharacterBase>(GetPawn());
	check(BaseCharacter)
	
	if (IsLocalController())
	{
		if (ULocalPlayer* LP = GetLocalPlayer())
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

void AProjectVillainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EIC) return;

	if (IA_Move) EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AProjectVillainPlayerController::Input_Move);
	if (IA_Look) EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AProjectVillainPlayerController::Input_Look);
	if (IA_Jump)
	{
		EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &AProjectVillainPlayerController::Input_JumpPressed);
		EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AProjectVillainPlayerController::Input_JumpReleased);
	}
	if (IA_Sprint)
	{
		EIC->BindAction(IA_Sprint, ETriggerEvent::Started, this, &AProjectVillainPlayerController::Input_SprintPressed);
		EIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AProjectVillainPlayerController::Input_SprintReleased);
	}
	if (IA_CrouchToggle)
		EIC->BindAction(IA_CrouchToggle, ETriggerEvent::Started, this, &AProjectVillainPlayerController::Input_CrouchToggle);
}

void AProjectVillainPlayerController::Input_Move(const FInputActionValue& Value)
{
	if (!BaseCharacter) return;

	const FVector2D Move = Value.Get<FVector2D>();
	const FRotator ControlRot = GetControlRotation();
	const FRotator YawRot(0.f, ControlRot.Yaw, 0.f);

	BaseCharacter->AddMovementInput(FRotationMatrix(YawRot).GetUnitAxis(EAxis::X), Move.Y);
	BaseCharacter->AddMovementInput(FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y), Move.X);
	BaseCharacter->SetActorRotation(YawRot);
}

void AProjectVillainPlayerController::Input_Look(const FInputActionValue& Value)
{
	const FVector2D Look = Value.Get<FVector2D>();
	AddYawInput(Look.X);
	AddPitchInput(Look.Y);
}

void AProjectVillainPlayerController::Input_JumpPressed(const FInputActionValue&)
{
	if (BaseCharacter) BaseCharacter->Jump();
}
void AProjectVillainPlayerController::Input_JumpReleased(const FInputActionValue&)
{
	if (BaseCharacter) BaseCharacter->StopJumping();
}
void AProjectVillainPlayerController::Input_SprintPressed(const FInputActionValue&)
{
	if (BaseCharacter) BaseCharacter->StartSprint();
}
void AProjectVillainPlayerController::Input_SprintReleased(const FInputActionValue&)
{
	if (BaseCharacter) BaseCharacter->StopSprint();
}
void AProjectVillainPlayerController::Input_CrouchToggle(const FInputActionValue&)
{
	if (BaseCharacter) BaseCharacter->ToggleCrouch();
}
