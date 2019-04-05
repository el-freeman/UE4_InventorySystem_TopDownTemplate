// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable.h"
#include "DrawDebugHelpers.h"
#include "ArpgCharacter.h"
#include "ArpgPlayerController.h"
#include "Kismet/GameplayStatics.h"

AInteractable::AInteractable()
{
	ItemID = FName("No ID");

	Name = "Interactable";
	Action = "Interact";

	// Set collisionsphere for check if character is overalapping interactable
	SphereRadius = 100.f;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionSphere->InitSphereRadius(SphereRadius);
	CollisionSphere->SetCollisionProfileName("Trigger");
	RootComponent = CollisionSphere;

	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractableMesh"));
	InteractableMesh->SetupAttachment(RootComponent);

	// For mouse hover action
	InteractableMesh->OnBeginCursorOver.AddDynamic(this, &AInteractable::OnBeginMouseOver);
	InteractableMesh->OnEndCursorOver.AddDynamic(this, &AInteractable::OnEndMouseOver);
		
	// for components overlapping action
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AInteractable::OnOverlapEnd);
	

}


void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;

	//DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 20, FColor::Purple, true, -1, 0, 1);
}

void AInteractable::Tick(float Deltaseconds)
{
	Super::Tick(Deltaseconds);
}

void AInteractable::Interact_Implementation(APlayerController* Controller)
{
	return;
}

FString AInteractable::GetItemName() const
{
	return FString::Printf(TEXT("%s"), *Name);
}

void AInteractable::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		auto ArpgCharacter = Cast<AArpgCharacter>(OtherActor);		
		if (ArpgCharacter != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("actor overlapped"));
			bool bOnActorOver = true;			
		}		
	}
}

void AInteractable::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("actor overlapped end"));
		auto ArpgCharacter = Cast<AArpgCharacter>(OtherActor);
		if (ArpgCharacter != nullptr)
		{
			bool bOnActorOver = false;
		}
	}
}

void AInteractable::OnBeginMouseOver(UPrimitiveComponent * TouchedComponent)
{
	if (TouchedComponent != nullptr)
	{				
		bOnMouseOver = true;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->CurrentMouseCursor = EMouseCursor::Hand;
		UE_LOG(LogTemp, Warning, TEXT("mouse overlapped"));
		
	}	
}

void AInteractable::OnEndMouseOver(UPrimitiveComponent * TouchedComponent)
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->CurrentMouseCursor = EMouseCursor::Default;
	bOnMouseOver = false;
	UE_LOG(LogTemp, Warning, TEXT("mouse overlapped end"));
	
}

