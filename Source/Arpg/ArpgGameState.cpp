// Fill out your copyright notice in the Description page of Project Settings.

#include "ArpgGameState.h"
#include "UObject/ConstructorHelpers.h"

AArpgGameState::AArpgGameState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> BP_ItemDB(TEXT("DataTable'/Game/Data/ItemDB.ItemDB'"));
	ItemDB = BP_ItemDB.Object;
}

UDataTable * AArpgGameState::GetItemDB() const
{
	return ItemDB;
}
