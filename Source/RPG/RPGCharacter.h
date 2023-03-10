// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hitable.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "RPGCharacter.generated.h"

UCLASS(Blueprintable)
class ARPGCharacter : public ACharacter, public IHitable
{
	GENERATED_BODY()

public:
	ARPGCharacter();
	virtual void Tick(float DeltaSeconds) override;
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool isSlashing;
	
protected:
	virtual void BeginPlay() override;
	
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	virtual void onHit_Implementation(int attack, int dmg) override;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Body;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Mind;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int initialDMG;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int initialSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=DATATABLES)
	UDataTable* ClassData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName className;
};

