#include "SurvivorCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ASurvivorCharacter::ASurvivorCharacter()
{
	WalkSpeed = 450.f;
	SprintSpeed = 650.f;
	CrouchSpeed = 250.f;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}
