// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "ManualPickup.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API AManualPickup : public AInteractable
{
	GENERATED_BODY()
	

public:
	AManualPickup();

	void Interact_Implementation(APlayerController* Controller) override;

protected:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemID;	
	
};
