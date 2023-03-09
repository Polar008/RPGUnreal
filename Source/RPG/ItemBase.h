// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipable.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class RPG_API AItemBase : public AActor, public IEquipable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FEquipableData mEquipableData;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
