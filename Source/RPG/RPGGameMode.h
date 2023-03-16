// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Turnable.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUp);

UCLASS(minimalapi)
class ARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	ARPGGameMode();

	virtual void BeginPlay() override;
	
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TurnSettings)
	TArray<TScriptInterface<ITurnable>> entitys;

	UPROPERTY(BlueprintReadOnly, Category = TurnSettings)
	int indexTurn;
	UPROPERTY(BlueprintAssignable)
	FOnLevelUp evOnLevelUp;
	
	UFUNCTION(BlueprintCallable)
	void GiveNextTurn();
	UFUNCTION(BlueprintCallable)
	void insertEntitys();
	UFUNCTION(BlueprintCallable)
	void RemoveEntity(TScriptInterface<ITurnable> entity);
	UFUNCTION(BlueprintCallable)
	inline TArray<TScriptInterface<ITurnable>> getEntities() const { return entitys; }

private:
	void SortByIbit();
};



