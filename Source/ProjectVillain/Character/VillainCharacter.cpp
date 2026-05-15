#include "VillainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AVillainCharacter::AVillainCharacter()
{
	WalkSpeed	= 550.f;
	SprintSpeed = 650.f;
	CrouchSpeed = 250.f;   

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}


