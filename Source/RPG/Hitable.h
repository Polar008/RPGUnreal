// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Hitable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHitable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPG_API IHitable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	int hp = 1;
	int ac = 10;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = HitSetting)
	void onHit(int attack, int dmg);
	
};
