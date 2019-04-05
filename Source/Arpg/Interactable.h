// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interactable.generated.h"

UCLASS()
class ARPG_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

protected:
	virtual void BeginPlay() override;


public:
	virtual void Tick(float Deltaseconds) override;

	UFUNCTION(BlueprintNativeEvent)
	void Interact(APlayerController* Controller);

	// For children class including AutoPicup and ManualPickup
	virtual void Interact_Implementation(APlayerController* Controller);

	UPROPERTY(EditDefaultsOnly)
	FString Name;
	UPROPERTY(EditDefaultsOnly)
	FString Action;

	// For widget to get item name when mouse cursor is over the item 
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	FString GetItemName() const;
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* InteractableMesh;

	UPROPERTY(EditAnywhere)
	float SphereRadius;	
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	bool GetIsOnOverlaped() { return bOnActorOver; }

	UFUNCTION()
	void OnBeginMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void OnEndMouseOver(UPrimitiveComponent* TouchedComponent);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	bool bOnActorOver;
	bool bOnMouseOver;


};
