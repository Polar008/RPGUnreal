// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "AIController.h"
#include "RPGGameMode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/WidgetComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	turnWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("QuemaElTeclado"));
	turnWidget->SetupAttachment(RootComponent);
	turnWidget->SetVisibility(false);
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

	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, true);
	turnWidget->AttachToComponent(GetMesh(), rules, TEXT("Head"));
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
		black->SetValueAsBool(FName("HasTurn"),false);
		gm->GiveNextTurn();
		black->ClearValue(FName("HasTurn"));
	}
	turnWidget->SetVisibility(false);
}

void AEnemyCharacter::startTurn_Implementation()
{
	
	if (black)
	{
		black->SetValueAsBool(FName("HasTurn"),true);
	}
	turnWidget->SetVisibility(true);
}

void AEnemyCharacter::onHit_Implementation(int attack, int dmg)
{
	if(attack >= ac)
	{
		hp-=dmg;
		if (hp<=0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Me muero"));
			gm->RemoveEntity(this);
			Destroy();
		}
	}
}

