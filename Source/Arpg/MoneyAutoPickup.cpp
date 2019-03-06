// Fill out your copyright notice in the Description page of Project Settings.

#include "MoneyAutoPickup.h"
#include "ArpgPlayerController.h"

AMoneyAutoPickup::AMoneyAutoPickup()
{
	Super::ItemID = FName("money");
	Value = 1;
}

void AMoneyAutoPickup::Collect_Implementation(APlayerController * Controller)
{
	AArpgPlayerController* IController = Cast<AArpgPlayerController>(Controller);
	IController->Money += Value;
	Destroy();
}
