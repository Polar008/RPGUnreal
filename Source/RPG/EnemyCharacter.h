// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hitable.h"
#include "Turnable.h"
#include "GameFramework/Character.h"
#include "Windows/WindowsPlatform.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class RPG_API AEnemyCharacter : public ACharacter, public ITurnable, public IHitable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	class UBlackboardComponent* black;
	class ARPGGameMode* gm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Widgets)
	class UWidgetComponent* turnWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isSlashing;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void endTurn_Implementation() override;
	virtual void startTurn_Implementation() override;

	FORCEINLINE UWidgetComponent* GetWidget() const { return turnWidget; }

	virtual void onHit_Implementation(int attack, int dmg) override;
};
