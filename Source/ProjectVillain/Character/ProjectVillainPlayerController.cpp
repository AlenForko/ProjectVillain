#include "ProjectVillainPlayerController.h"
#include "CharacterBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AProjectVillainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CachePossessedCharacter();
	if (IsLocalController())
	{
		if (ULocalPlayer* LP = GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (PlayerMappingContext)
				{
					Subsystem->AddMappingContext(PlayerMappingContext, 0);
				}
			}
		}
	}
}

void AProjectVillainPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	CachePossessedCharacter(InPawn);
}

void AProjectVillainPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	CachePossessedCharacter(P);
}

void AProjectVillainPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	CachedBaseCharacter = nullptr;
}

void AProjectVillainPlayerController::CachePossessedCharacter(APawn* InPawn)
{
	APawn* PossessedPawn = InPawn;
	if (!PossessedPawn)
	{
		PossessedPawn = GetPawn();
	}

	CachedBaseCharacter = Cast<ACharacterBase>(PossessedPawn);
}

ACharacterBase* AProjectVillainPlayerController::GetControlledCharacter()
{
	if (!CachedBaseCharacter)
	{
		CachePossessedCharacter();
	}

	return CachedBaseCharacter.Get();
}

void AProjectVillainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComp) return;

	if (IA_Move)
		EnhancedInputComp->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AProjectVillainPlayerController::Input_Move);

	if (IA_Look)
		EnhancedInputComp->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AProjectVillainPlayerController::Input_Look);

	if (IA_Jump)
	{
		EnhancedInputComp->BindAction(IA_Jump, ETriggerEvent::Started, this, &AProjectVillainPlayerController::Input_JumpStarted);
		EnhancedInputComp->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AProjectVillainPlayerController::Input_JumpCompleted);
	}

	if (IA_Sprint)
	{
		EnhancedInputComp->BindAction(IA_Sprint, ETriggerEvent::Started, this, &AProjectVillainPlayerController::Input_SprintStarted);
		EnhancedInputComp->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AProjectVillainPlayerController::Input_SprintCompleted);
	}

	if (IA_CrouchToggle)
		EnhancedInputComp->BindAction(IA_CrouchToggle, ETriggerEvent::Started, this, &AProjectVillainPlayerController::Input_CrouchToggle);
}

void AProjectVillainPlayerController::Input_Move(const FInputActionValue& Value)
{
	const FVector2D MoveAxis = Value.Get<FVector2D>();
	if (ACharacterBase* ControlledCharacter = GetControlledCharacter())
	{
		ControlledCharacter->HandleMoveInput(MoveAxis);
	}
}

void AProjectVillainPlayerController::Input_Look(const FInputActionValue& Value)
{
	const FVector2D LookAxis = Value.Get<FVector2D>();
	if (ACharacterBase* ControlledCharacter = GetControlledCharacter())
	{
		ControlledCharacter->HandleLookInput(LookAxis);
	}
}

void AProjectVillainPlayerController::Input_JumpStarted(const FInputActionValue& /*Value*/)
{
	if (ACharacterBase* ControlledCharacter = GetControlledCharacter())
	{
		ControlledCharacter->HandleJumpPressed();
	}
}

void AProjectVillainPlayerController::Input_JumpCompleted(const FInputActionValue& /*Value*/)
{
	if (ACharacterBase* ControlledCharacter = GetControlledCharacter())
	{
		ControlledCharacter->HandleJumpReleased();
	}
}

void AProjectVillainPlayerController::Input_SprintStarted(const FInputActionValue& /*Value*/)
{
	if (ACharacterBase* ControlledCharacter = GetControlledCharacter())
	{
		ControlledCharacter->StartSprint();
	}
}

void AProjectVillainPlayerController::Input_SprintCompleted(const FInputActionValue& /*Value*/)
{
	if (ACharacterBase* ControlledCharacter = GetControlledCharacter())
	{
		ControlledCharacter->StopSprint();
	}
}

void AProjectVillainPlayerController::Input_CrouchToggle(const FInputActionValue& /*Value*/)
{
	if (ACharacterBase* ControlledCharacter = GetControlledCharacter())
	{
		ControlledCharacter->ToggleCrouch();
	}
}
