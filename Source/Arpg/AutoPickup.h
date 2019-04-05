// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "AutoPickup.generated.h"

UCLASS()
class ARPG_API AAutoPickup : public AInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAutoPickup();

	UFUNCTION(BlueprintNativeEvent)
	void Collect(APlayerController* Controller);
	virtual void Collect_Implementation(APlayerController* Controller);

	FName GetItemID();
};
