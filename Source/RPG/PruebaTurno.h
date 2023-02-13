// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turnable.h"
#include "GameFramework/Actor.h"
#include "RPGGameMode.h"
#include "PruebaTurno.generated.h"


UCLASS()
class RPG_API APruebaTurno : public AActor,public ITurnable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APruebaTurno();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	ARPGGameMode* gm;
	virtual void endTurn_Implementation() override;
	virtual void startTurn_Implementation() override;
	FTimerHandle th;
	UWorld* w =  GetWorld();
};
