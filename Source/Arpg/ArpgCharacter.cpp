// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ArpgCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "ArpgPlayerController.h"
#include "Materials/Material.h"
#include "Interactable.h"
#include "AutoPickup.h"
#include "InventoryItem.h"
#include "Engine/World.h"

AArpgCharacter::AArpgCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Attach a skeletal mesh
	GetMesh()->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Shinbi(TEXT("SkeletalMesh'/Game/ParagonShinbi/Characters/Heroes/Shinbi/Meshes/Shinbi.Shinbi'"));
	if (Shinbi.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(Shinbi.Object);
	}

	// Make skeletal mesh face front side
	GetMesh()->SetRelativeRotation(FRotator(0.f, 270.f, 0.f));
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -98.f));

	// Attach animation blueprint
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> PlayerAnim(TEXT("/Game/TopDownCPP/Blueprints/PlayerAnimBP.PlayerAnimBP_C"));
	if (PlayerAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PlayerAnim.Class);
	}


	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 800.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create the collection sphere for inventory system
	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	CollectionSphere->SetupAttachment(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1800.f;
	CameraBoom->RelativeRotation = FRotator(-55.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	TopDownCameraComponent->SetFieldOfView(75.f);

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Create HPBar UI
	// UILocation needs to be modified when screen size or FOV changed
	HPBarWidget = CreateDefaultSubobject <UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget->SetupAttachment(GetMesh());
	HPBarWidget->SetRelativeLocation(FVector(0.f, 0.f, 270.f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/UI/UI_HPBar.UI_HPBar_C'"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(100.f, 30.f));
	}

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;


}

void AArpgCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}

	// Find items for manual picup
	CheckForInteractables();

	// Find items can be colledted automatically
	CollectAutoPickups();	
}


void AArpgCharacter::CollectAutoPickups()
{
	// Get all overlapping Actors and store them in an array
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);

	AArpgPlayerController* IController = Cast<AArpgPlayerController>(GetController());

	
	// For each Actor we collected	
	for(AActor* Pickup : CollectedActors)
	{
		// Cast the actor to AAutoPickup
		AAutoPickup* const TestPickup = Cast<AAutoPickup>(Pickup);
		// If the cast is successful and the pickup is valid and active 
		if (TestPickup && !TestPickup->IsPendingKill())
		{
			TestPickup->Collect(IController);
		}
	}
}


void AArpgCharacter::CheckForInteractables()
{	
	AArpgPlayerController* PC = Cast<AArpgPlayerController>(GetController());	
	if (PC)
	{		
		FHitResult HitResult;
		PC->GetHitResultUnderCursor(ECC_Visibility, true, HitResult);
		AInteractable* Interactable = Cast<AInteractable>(HitResult.GetActor());

		float const Distance = FVector::Dist(HitResult.ImpactPoint, this->GetActorLocation());
		
		// Check mouse cursor is on the item && Distance between item and character is close enough
		if (Interactable && (Distance < 350.0f))
		{			
			
			PC->CurrentInteractable = Interactable;
			UE_LOG(LogTemp, Warning, (TEXT("Active CurrentInteracable")));
			return;						
		}		
	}
	PC->CurrentInteractable = nullptr;	
}
