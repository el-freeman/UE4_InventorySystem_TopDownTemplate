// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Arpg.h"
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "ArpgGameInstance.generated.h"

// Struct for character status
USTRUCT(BlueprintType)
struct FArpgCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FArpgCharacterData():Level(1), MaxHP(100.f), Attack(10.f), DropExp(10), NextExp(30){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;
};

/**
 * 
 */
UCLASS()
class ARPG_API UArpgGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UArpgGameInstance();

	virtual void Init() override;

	FArpgCharacterData* GetArpgCharacterData(int32 Level);

private:
	UPROPERTY()
	class UDataTable* ArpgCharacterTable;
	
	
};
