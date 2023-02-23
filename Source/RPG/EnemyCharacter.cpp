// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "AIController.h"
#include "RPGGameMode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	gm = Cast<ARPGGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	auto aic = UAIBlueprintHelperLibrary::GetAIController(this);
	if (aic)
	{
		UE_LOG(LogTemp, Display, TEXT("2"));
		black = aic->GetBlackboardComponent();
		if (black)
			UE_LOG(LogTemp, Display, TEXT("3"));
	}
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::endTurn_Implementation()
{
	if (black)
	{
		UE_LOG(LogTemp, Display, TEXT("SIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII"));
		black->SetValueAsBool(FName("HasTurn"),false);
		gm->GiveNextTurn();
		black->ClearValue(FName("HasTurn"));
	}
}

void AEnemyCharacter::startTurn_Implementation()
{
	
	if (black)
	{
		UE_LOG(LogTemp, Display, TEXT("cum in black"));

		black->SetValueAsBool(FName("HasTurn"),true);
	}
}

