// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ArpgPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "ArpgCharacter.h"
#include "ArpgGameState.h"
#include "Engine/World.h"

AArpgPlayerController::AArpgPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	InventorySlotLimit = 50;
	InventoryWeightLimit = 500;
}


int32 AArpgPlayerController::GetInventoryWeight()
{
	int32 Weight = 0;
	for (auto& Item : Inventory)
	{
		Weight += Item.Weight;
	}

	return Weight;
}

bool AArpgPlayerController::AddItemToInventoryByID(FName ID)
{
	AArpgGameState* GameState = Cast<AArpgGameState>(GetWorld()->GetGameState());
	UDataTable* ItemTable = GameState->GetItemDB();
	FInventoryItem* ItemToAdd = ItemTable->FindRow<FInventoryItem>(ID, "");

	if (ItemToAdd)
	{
		// If you dont want a Slot- or WeightLimit you have to remove it in this line
		if (Inventory.Num() < InventorySlotLimit && GetInventoryWeight() + ItemToAdd->Weight <= InventoryWeightLimit)
		{
			Inventory.Add(*ItemToAdd);
			ReloadInventory();
			return true;
		}
	}
	return false;
}

void AArpgPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AArpgPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AArpgPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AArpgPlayerController::OnSetDestinationReleased);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AArpgPlayerController::Interact);
}


void AArpgPlayerController::MoveToMouseCursor()
{
	
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
	
}

void AArpgPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 100.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AArpgPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AArpgPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AArpgPlayerController::Interact()
{
	if (CurrentInteractable)
	{
		CurrentInteractable->Interact(this);
	}
}
