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
	indexTurn = 0;
}

void ARPGGameMode::SortByIbit()
{
	entitys.Sort([](const TScriptInterface<ITurnable>& i1, const TScriptInterface<ITurnable>& i2)
	{
		if(!i1.GetInterface())
			return true;
		if(!i2.GetInterface())
			return false;
		return i1.GetInterface()->initative < i2.GetInterface()->initative;
	});
}

void ARPGGameMode::GiveNextTurn()
{
	if(this==NULL)return;
	//if (entitys.Num() > indexTurn++ % entitys.Num())
	//	entitys[indexTurn % entitys.Num()]->startTurn_Implementation();
	UE_LOG(LogTemp, Display, TEXT("Index de entitys %d"),indexTurn);
	//UE_LOG(LogTemp, Display, TEXT("Giving next turn from %s -> %s"), *entitys[indexTurn].GetObject()->GetName(), *entitys[indexTurn+1%entitys.Num()].GetObject()->GetName());
	if (indexTurn == entitys.Num())
	{
		indexTurn = 0;
	}
	if (indexTurn < entitys.Num())
	{
		//Cast<ITurnable>(entitys[indexTurn].GetObject())->startTurn_Implementation();
		entitys[indexTurn]->Execute_startTurn(entitys[indexTurn].GetObject());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Turn of :%s"), *entitys[indexTurn].GetObject()->GetName()));
		indexTurn++;
		if (indexTurn == entitys.Num())
		{
			indexTurn = 0;
		}
	}
}

void ARPGGameMode::insertEntitys()
{
	TArray<AActor*> OutAct;
	UGameplayStatics::GetAllActorsWithInterface(this, UTurnable::StaticClass(), OutAct);
	for (AActor* act : OutAct)
	{
		TScriptInterface<ITurnable> Turn = act;
		entitys.Add(Turn);
		UE_LOG(LogTemp, Display, TEXT("insertado %s en Entitys"), *Turn.GetObject()->GetName());
	}
	SortByIbit();
}

void ARPGGameMode::RemoveEntity(TScriptInterface<ITurnable> entity)
{
	entitys.Remove(entity);
}

