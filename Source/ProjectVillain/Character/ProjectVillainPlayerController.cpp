#include "ProjectVillainPlayerController.h"
#include "CharacterBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AProjectVillainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Add mapping context for LOCAL player only
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
	CachePossessedCharacter();
}

void AProjectVillainPlayerController::CachePossessedCharacter()
{
	CachedBaseCharacter = Cast<ACharacterBase>(GetPawn());
	if (CachedBaseCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("CachedBaseCharacter assigned: %s"), *CachedBaseCharacter->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CachedBaseCharacter NOT assigned (GetPawn returned null or not ACharacterBase)"));
	}
}

void AProjectVillainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EIC) return;

	if (IA_Move)
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AProjectVillainPlayerController::Input_Move);

	if (IA_Look)
		EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AProjectVillainPlayerController::Input_Look);

	if (IA_Jump)
	{
		EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &AProjectVillainPlayerController::Input_JumpStarted);
		EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AProjectVillainPlayerController::Input_JumpCompleted);
	}

	if (IA_Sprint)
	{
		EIC->BindAction(IA_Sprint, ETriggerEvent::Started, this, &AProjectVillainPlayerController::Input_SprintStarted);
		EIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AProjectVillainPlayerController::Input_SprintCompleted);
	}

	if (IA_CrouchToggle)
		EIC->BindAction(IA_CrouchToggle, ETriggerEvent::Started, this, &AProjectVillainPlayerController::Input_CrouchToggle);
}

void AProjectVillainPlayerController::Input_Move(const FInputActionValue& Value)
{
	if (!CachedBaseCharacter) CachePossessedCharacter();
	if (!CachedBaseCharacter) return;

	const FVector2D MoveAxis = Value.Get<FVector2D>();
	CachedBaseCharacter->HandleMoveInput(MoveAxis);
}

void AProjectVillainPlayerController::Input_Look(const FInputActionValue& Value)
{
	if (!CachedBaseCharacter) CachePossessedCharacter();
	if (!CachedBaseCharacter) return;

	const FVector2D LookAxis = Value.Get<FVector2D>();
	CachedBaseCharacter->HandleLookInput(LookAxis);
}

void AProjectVillainPlayerController::Input_JumpStarted(const FInputActionValue& /*Value*/)
{
	if (!CachedBaseCharacter) CachePossessedCharacter();
	if (CachedBaseCharacter) CachedBaseCharacter->HandleJumpPressed();
}

void AProjectVillainPlayerController::Input_JumpCompleted(const FInputActionValue& /*Value*/)
{
	if (!CachedBaseCharacter) CachePossessedCharacter();
	if (CachedBaseCharacter) CachedBaseCharacter->HandleJumpReleased();
}

void AProjectVillainPlayerController::Input_SprintStarted(const FInputActionValue& /*Value*/)
{
	if (!CachedBaseCharacter) CachePossessedCharacter();
	if (CachedBaseCharacter) CachedBaseCharacter->StartSprint();
}

void AProjectVillainPlayerController::Input_SprintCompleted(const FInputActionValue& /*Value*/)
{
	if (!CachedBaseCharacter) CachePossessedCharacter();
	if (CachedBaseCharacter) CachedBaseCharacter->StopSprint();
}

void AProjectVillainPlayerController::Input_CrouchToggle(const FInputActionValue& /*Value*/)
{
	if (!CachedBaseCharacter) CachePossessedCharacter();
	if (CachedBaseCharacter) CachedBaseCharacter->ToggleCrouch();
}
