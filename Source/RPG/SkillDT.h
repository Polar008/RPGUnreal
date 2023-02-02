// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillDT.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct RPG_API FSkillDT : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class ASkill> skill;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int dmg;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float duration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Position;
	
	FSkillDT() : skill(nullptr), dmg(0), duration(1), Position(FVector(0,0,0)) {}
};
