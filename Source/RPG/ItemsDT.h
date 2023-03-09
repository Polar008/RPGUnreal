// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillDT.h"
#include "Engine/DataTable.h"
#include "ItemsDT.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct RPG_API FItemsDT : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	struct FSkillDT skill;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int hpIncrease;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int dmgIncrease;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int acIncrease;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int slot;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> ownwer;
	

	FItemsDT() : skill(), hpIncrease(0), dmgIncrease(0), acIncrease(0), slot(0), ownwer(nullptr) {}
};
