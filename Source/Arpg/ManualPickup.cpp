// Fill out your copyright notice in the Description page of Project Settings.

#include "ManualPickup.h"
#include "ArpgPlayerController.h"


AManualPickup::AManualPickup()
{
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	RootComponent = Cast<USceneComponent>(PickupMesh);

	ItemID = FName("No ID");

	Super::Name = "Item";
	Super::Action = "pickup";
}

void AManualPickup::Interact_Implementation(APlayerController * Controller)
{
	Super::Interact_Implementation(Controller);

	/* TO DO after finishing Arpgplayercontoller coding
	AArpgPlayerController* IController = Cast<AArpgPlayerController>(Controller);
	if (IController->AddItemToInventoryByID(ItemID))
		Destroy();
	*/
}
