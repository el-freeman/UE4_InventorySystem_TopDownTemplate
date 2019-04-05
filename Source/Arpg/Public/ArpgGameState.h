// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameStateBase.h"
#include "ArpgGameState.generated.h"

UCLASS()
class ARPG_API AArpgGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AArpgGameState();

	UDataTable* GetItemDB() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	class UDataTable* ItemDB;
	
	
};
