// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ProjectVillainPlayerState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
	Survivor,
	Villain
};

UCLASS()
class PROJECTVILLAIN_API AProjectVillainPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AProjectVillainPlayerState();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	void SetPlayerRole(EPlayerRole NewRole);
	
	EPlayerRole GetPlayerRole() const { return PlayerRole; }
	
protected:
	UPROPERTY(ReplicatedUsing=OnRep_PlayerRole, BlueprintReadOnly, Category="Player State")
	EPlayerRole PlayerRole = EPlayerRole::Survivor;
	
	UFUNCTION()
	void OnRep_PlayerRole();
};
