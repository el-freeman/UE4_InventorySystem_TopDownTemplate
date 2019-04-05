// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterStatComponent.h"
#include "ArpgGameInstance.h"


// Sets default values for this component's properties
UCharacterStatComponent::UCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
	// ...
}


// Called when the game starts
void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}

void UCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	UE_LOG(LogTemp, Warning, TEXT("statcomp initialcomp"));
	SetNewLevel(Level);
}

void UCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	
	auto ArpgGameInstance = Cast<UArpgGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (ArpgGameInstance != nullptr)
	{
		CurrentStatData = ArpgGameInstance->GetArpgCharacterData(NewLevel);
		if (CurrentStatData != nullptr)
		{
			//when level change, current hp also change to new level's max hp
			Level = NewLevel;
			CurrentHP = CurrentStatData->MaxHP;
			UE_LOG(LogTemp, Warning, TEXT("set new level succeed"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Level data doesn't exit"));
		}
	}
}


// Called every frame
//void UCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

