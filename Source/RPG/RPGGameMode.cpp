// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGGameMode.h"
#include "RPGPlayerController.h"
#include "RPGCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"


ARPGGameMode::ARPGGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARPGPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
		TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void ARPGGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ARPGGameMode::SortByIbit()
{
	entitys.Sort([](const TScriptInterface<ITurnable>& i1, const TScriptInterface<ITurnable>& i2)
	{
		return i1.GetInterface()->initative < i2.GetInterface()->initative;
	});
}

void ARPGGameMode::GiveNextTurn()
{
	if (entitys.Num() > 0)
		entitys[indexTurn++ % entitys.Num()].GetInterface()->startTurn_Implementation();
}

void ARPGGameMode::insertEntitys()
{
	TArray<AActor*> OutAct;
	UGameplayStatics::GetAllActorsWithInterface(this, UTurnable::StaticClass(), OutAct);
	for (AActor* act : OutAct)
	{
		TScriptInterface<ITurnable> Turn = act;
		entitys.Add(Turn);
	}
}
