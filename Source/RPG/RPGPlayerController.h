// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hitable.h"
#include "RPGCharacter.h"
#include "RPGGameMode.h"
#include "SkillDT.h"
#include "Turnable.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "RPGPlayerController.generated.h"


class ARPGCharacter;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkill, AActor*, enemy, FSkillDT, skill);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttack, AActor*, enemy);

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class ARPGPlayerController : public APlayerController,public ITurnable
{
	GENERATED_BODY()

public:
	ARPGPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	UPROPERTY(BlueprintAssignable)
	FOnSkill evOnSkill;
	UPROPERTY(BlueprintAssignable)
	FOnAttack evOnAttack;

	UFUNCTION(BlueprintCallable)
	ARPGCharacter* getMyPlayerCharacter() const { return Cast<ARPGCharacter>(GetPawn()); }
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnRightTouchPressed();
	void On1SkillPressed();
	void On2SkillPressed();
	void On3SkillPressed();
	void OnEndTurnPressed();
	virtual void BeginPlay() override;
	FVector CheckDistance(FVector playerPos, FVector destination);

private:
	bool bInputPressed; // Input is bring pressed
	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
	ARPGGameMode* gm;

public:
	bool hasTurn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TurnSettings)
	bool canRun = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TurnSettings)
	bool canAttack = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TurnSettings)
	float maxMoveDistance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=DATATABLES)
	UDataTable* ClassData;
	UPROPERTY(BlueprintReadWrite, BlueprintReadWrite)
	FName className; 

	
	

	
	virtual void endTurn_Implementation() override;
	virtual void startTurn_Implementation() override;

};


