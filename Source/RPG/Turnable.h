// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/Interface.h"
#include "Turnable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTurnable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPG_API ITurnable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	int initative;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = TurnSettings)
	void startTurn();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = TurnSettings)
	void endTurn();
	
};
