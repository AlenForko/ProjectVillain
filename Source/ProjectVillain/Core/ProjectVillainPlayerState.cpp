// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectVillainPlayerState.h"

#include "Net/UnrealNetwork.h"

AProjectVillainPlayerState::AProjectVillainPlayerState()
{
	bReplicates = true;
}

void AProjectVillainPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AProjectVillainPlayerState, PlayerRole)
}

void AProjectVillainPlayerState::OnRep_PlayerRole()
{
	// UPDATE UI
}

void AProjectVillainPlayerState::SetPlayerRole(EPlayerRole NewRole)
{
	if (HasAuthority()) PlayerRole = NewRole;	
}

