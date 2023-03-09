// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGCharacter.h"

#include "ClassData.h"
#include "ItemsDT.h"
#include "K2Node_SpawnActorFromClass.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/DataTable.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"


ARPGCharacter::ARPGCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	turnWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("QuemaElTeclado"));
	turnWidget->SetupAttachment(RootComponent);
	turnWidget->SetVisibility(false);

	equipedItems.Add(TEXT(""));
	equipedItems.Add(TEXT(""));
	equipedItems.Add(TEXT(""));
}

void ARPGCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ARPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	static const FString context = FString("Getting stats");
	FClassData* clase = ClassData->FindRow<FClassData>(className, context, true);

	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, true);
	turnWidget->AttachToComponent(GetMesh(), rules, TEXT("Head"));
	hp = 3;

	if(clase)
	{
		Body = clase->initialBody;
		Mind = clase->initialMind;
		DMG = clase->initialDMG;
	}
	ac = 10 + Body;
}

void ARPGCharacter::onHit_Implementation(int attack, int dmg)
{
	if(attack >= ac)
	{
		hp-=dmg;
		if (hp<=0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Me muero"));
		}
	}
}

void ARPGCharacter::EquipItem(FName itemName)
{
	static const FString context = FString("Getting skill1");
	FItemsDT* item = items->FindRow<FItemsDT>(itemName, context, true);
	if(equipedItems[item->slot] != "")
	{
		UnEquipItem(equipedItems[item->slot]);

	}
	DMG += item->dmgIncrease;
	hp += item->hpIncrease;
	ac += item->acIncrease;
}

void ARPGCharacter::UnEquipItem(FName itemName)
{
	static const FString context = FString("Getting skill1");
	FItemsDT* item = items->FindRow<FItemsDT>(itemName, context, true);
	DMG -= item->dmgIncrease;
	hp -= item->hpIncrease;
	ac -= item->acIncrease;
	FActorSpawnParameters SpawnInfo;
	auto* it =  GetWorld()->SpawnActor<AActor>(item->ownwer->GetClass(), GetActorLocation(), GetActorRotation(), SpawnInfo);
}
