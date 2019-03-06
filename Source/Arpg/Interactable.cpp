// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable.h"


AInteractable::AInteractable()
{
	Name = "Interactable";
	Action = "Interact";
}

void AInteractable::Interact_Implementation(APlayerController* Controller)
{
	return;
}

FString AInteractable::GetInteractText() const
{
	return FString::Printf(TEXT("%s: Press F to %s"), *Name, *Action);
}
