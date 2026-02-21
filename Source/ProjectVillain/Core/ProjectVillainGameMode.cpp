// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectVillainGameMode.h"

#include "ProjectVillainGameState.h"
#include "ProjectVillainPlayerState.h"

AProjectVillainGameMode::AProjectVillainGameMode()
{
	DefaultPawnClass = AProjectVillainPlayerState::StaticClass();
	GameStateClass   = AProjectVillainGameState::StaticClass();
}

void AProjectVillainGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (AProjectVillainGameState* PVGameState = GetGameState<AProjectVillainGameState>())
	{
		PVGameState->StartMatchTimer();
	}
}

void AProjectVillainGameMode::PostLogin(APlayerController* NewPlayerController)
{
	Super::PostLogin(NewPlayerController);
	
	AProjectVillainPlayerState* PlayerState = NewPlayerController->GetPlayerState<AProjectVillainPlayerState>();
	if (!PlayerState) return;
	
	if (!bVillainAssigned)
	{
		PlayerState->SetPlayerRole(EPlayerRole::Villain);
		bVillainAssigned = true;
		UE_LOG(LogTemp, Warning, TEXT("Player %s assigned as Villain"), *PlayerState->GetPlayerName());
	}
	else
	{
		PlayerState->SetPlayerRole(EPlayerRole::Survivor);
		UE_LOG(LogTemp, Warning, TEXT("Player %s assigned as Survivor"), *PlayerState->GetPlayerName());
	}
}

APawn* AProjectVillainGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
	
	AProjectVillainPlayerState* PlayerState = NewPlayer->GetPlayerState<AProjectVillainPlayerState>();
	if (!PlayerState) return nullptr;

	TSubclassOf<APawn> PawnToSpawn = SurvivorPawnClass;

	if (PlayerState->GetPlayerRole() == EPlayerRole::Villain)
	{
		PawnToSpawn = VillainPawnClass;
	}

	return GetWorld()->SpawnActor<APawn>(
		PawnToSpawn,
		StartSpot->GetActorLocation(),
		StartSpot->GetActorRotation()
	);
}

