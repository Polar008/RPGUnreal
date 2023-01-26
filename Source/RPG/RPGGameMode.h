// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Turnable.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameMode.generated.h"



UCLASS(minimalapi)
class ARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	ARPGGameMode();

	virtual void BeginPlay() override;
	

	UPROPERTY(BlueprintReadOnly, Category = TurnSettings)
	int indexTurn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TurnSettings)
	TArray<TScriptInterface<ITurnable>> entitys;
	void SortByIbit();
	UFUNCTION(BlueprintCallable)
	void GiveNextTurn();
	UFUNCTION(BlueprintCallable)
	void insertEntitys();
};



