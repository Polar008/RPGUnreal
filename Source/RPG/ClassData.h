// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ClassData.generated.h"
UENUM(BlueprintType)
enum EClases {
	MAGE,
	WARRIOR,
	RANGER
	
};
/**
 * 
 */
USTRUCT(BlueprintType)
struct RPG_API FClassData : public FTableRowBase 
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EClases> myclass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int initialBody;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int initialMind;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int bodyOnLvl;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int mindOnLvl;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int initialDMG;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int initialSpeed;
	
	
	FClassData() : myclass(WARRIOR), initialBody(0), initialMind(0), bodyOnLvl(0), mindOnLvl(0), initialDMG(4), initialSpeed(500){}
};
