// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectVillainGameMode.h"

#include "ProjectVillainGameState.h"
#include "ProjectVillainPlayerState.h"
#include "ProjectVillain/Character/ProjectVillainPlayerController.h"

AProjectVillainGameMode::AProjectVillainGameMode()
{
	PlayerStateClass = AProjectVillainPlayerState::StaticClass();
	GameStateClass   = AProjectVillainGameState::StaticClass();
	PlayerControllerClass = AProjectVillainPlayerController::StaticClass();
}

void AProjectVillainGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (AProjectVillainGameState* PVGameState = GetGameState<AProjectVillainGameState>())
	{
		PVGameState->StartMatchTimer();
	}
}

AActor* AProjectVillainGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if (AProjectVillainPlayerState* PlayerState = Player->GetPlayerState<AProjectVillainPlayerState>())
	{
		const EPlayerRole AssignedRole = bVillainAssigned ? EPlayerRole::Survivor : EPlayerRole::Villain;
		
		PlayerState->SetPlayerRole(AssignedRole);
		
		if (AssignedRole == EPlayerRole::Villain)
		{
			bVillainAssigned = true;
		}
		UE_LOG(LogTemp, Warning, TEXT("Player %s assigned as %s (ChoosePlayerStart)"), *PlayerState->GetPlayerName(), AssignedRole == EPlayerRole::Villain ? TEXT("Villain") : TEXT("Survivor"));
	}
	return Super::ChoosePlayerStart_Implementation(Player);
}

APawn* AProjectVillainGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
	const AProjectVillainPlayerState* PlayerState = NewPlayer->GetPlayerState<AProjectVillainPlayerState>();
	if (!PlayerState)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerState is null for Player %s"), *NewPlayer->GetName());
		return nullptr;
	}

	const TSubclassOf<APawn> PawnToSpawn = PlayerState->GetPlayerRole() == EPlayerRole::Villain ? VillainPawnClass : SurvivorPawnClass;

	return GetWorld()->SpawnActor<APawn>(
		PawnToSpawn,
		StartSpot->GetActorLocation(),
		StartSpot->GetActorRotation()
	);
}
