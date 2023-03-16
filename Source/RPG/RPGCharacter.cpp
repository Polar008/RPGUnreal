// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGCharacter.h"

#include "ClassData.h"
#include "ItemBase.h"
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
#include "Microsoft/COMPointer.h"


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
	
}

void ARPGCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ARPGCharacter::BeginPlay()
{
	equipedItems.Add(TEXT(""));
	equipedItems.Add(TEXT(""));
	equipedItems.Add(TEXT(""));
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

void ARPGCharacter::EquipItem(const FName& itemName)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Equiped")));

	static const FString context = FString("Getting item to equip");
	FItemsDT* item = items->FindRow<FItemsDT>(itemName, context, true);
	if(equipedItems[item->slot] != TEXT(""))
	{
		UnEquipItem(equipedItems[item->slot]);

	}
	equipedItems[item->slot] = itemName;
	DMG += item->dmgIncrease;
	hp += item->hpIncrease;
	ac += item->acIncrease;
}

void ARPGCharacter::UnEquipItem(const FName& itemName)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("unEquiped")));

	static const FString context = FString("Getting item to drop");
	FItemsDT* item = items->FindRow<FItemsDT>(itemName, context, true);
	DMG -= item->dmgIncrease;
	hp -= item->hpIncrease;
	ac -= item->acIncrease;
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	const FVector& pos {GetActorLocation()};
	const FRotator& rot {GetActorRotation()};
	GetWorld()->SpawnActor<AItemBase>(item->ownwer, pos, rot, SpawnInfo);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Afterspawn")));
}

void ARPGCharacter::LvlUp(int vida, int armadura, int male)
{
	ac += armadura;
	hp += vida;
	DMG += male;
}
