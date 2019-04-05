// Fill out your copyright notice in the Description page of Project Settings.

#include "ArpgGameInstance.h"

UArpgGameInstance::UArpgGameInstance()
{
	// Set up data table for character status
	FString CharacterDataPath = TEXT("DataTable'/Game/Data/ArpgCharacterData.ArpgCharacterData'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ArpgCharacter(*CharacterDataPath);
	if (DT_ArpgCharacter.Succeeded())
	{
		ArpgCharacterTable = DT_ArpgCharacter.Object;
	}
}

void UArpgGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Game intstace init"));
}

FArpgCharacterData * UArpgGameInstance::GetArpgCharacterData(int32 Level)
{
	return ArpgCharacterTable->FindRow<FArpgCharacterData>(*FString::FromInt(Level), TEXT(""));
}
