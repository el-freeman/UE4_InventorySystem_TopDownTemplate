// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable.h"
#include "ArpgCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "ArpgPlayerController.h"


AInteractable::AInteractable()
{
	Name = "Interactable";
	Action = "Interact";

	Trigger->SetCollisionProfileName(TEXT("Interactable"));
}

void AInteractable::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractable::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnCharacterOverlap);
}

void AInteractable::OnCharacterOverlap(UPrimitiveComponent * OverlapComp, AActor * OtherActor, UPrimitiveComponent * OhterComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	auto ArpgCharacter = Cast<AArpgCharacter>(OtherActor);
	if (nullptr != ArpgCharacter)
	{
		ArpgCharacter->CheckForInteractables();
	}
	
}

void AInteractable::Interact_Implementation(APlayerController* Controller)
{
	return;
}

FString AInteractable::GetInteractText() const
{
	return FString::Printf(TEXT("%s: Press F to %s"), *Name, *Action);
}
