// Fill out your copyright notice in the Description page of Project Settings.


#include "PruebaTurno.h"
#include "RPGGameMode.h"

// Sets default values
APruebaTurno::APruebaTurno()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	gm = Cast<ARPGGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called when the game starts or when spawned
void APruebaTurno::BeginPlay()
{
	Super::BeginPlay();
	initative = 19;
}

// Called every frame
void APruebaTurno::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APruebaTurno::endTurn_Implementation()
{
	gm->GiveNextTurn();
}

void APruebaTurno::startTurn_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("me la chupas"));
	w->GetTimerManager().SetTimer(th,this, &APruebaTurno::endTurn_Implementation,5,false);
}


