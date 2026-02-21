// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectVillainGameMode.h"

#include "Character/SurvivorCharacter.h"

AProjectVillainGameMode::AProjectVillainGameMode()
{
	DefaultPawnClass = ASurvivorCharacter::StaticClass();
}
