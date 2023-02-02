// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "RPGCharacter.h"
#include "VectorTypes.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ARPGPlayerController::ARPGPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	gm = Cast<ARPGGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ARPGPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bInputPressed)
	{
		FollowTime += DeltaTime;

		// Look for the touch location
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		if (bIsTouch)
		{
			GetHitResultUnderFinger(ETouchIndex::Touch1, ECC_Visibility, true, Hit);
		}
		else
		{
			GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		}
		HitLocation = Hit.Location;

		// Direct the Pawn towards that location
		// if(MyPawn)
		// {
		// 	FVector WorldDirection = (HitLocation - MyPawn->GetActorLocation()).GetSafeNormal();
		// 	MyPawn->AddMovementInput(WorldDirection, 1.f, false);
		// }
	}
	else
	{
		FollowTime = 0.f;
	}
}

void ARPGPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ARPGPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ARPGPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ARPGPlayerController::OnRightTouchPressed);
	
	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ARPGPlayerController::OnTouchPressed);
	InputComponent->BindTouch(EInputEvent::IE_Released, this, &ARPGPlayerController::OnTouchReleased);
}

void ARPGPlayerController::OnSetDestinationPressed()
{
	// We flag that the input is being pressed
	bInputPressed = true;
	// Just in case the character was moving because of a previous short press we stop it
	StopMovement();
}

void ARPGPlayerController::OnSetDestinationReleased()
{
	// Player is no longer pressing the input
	bInputPressed = false;

	// If it was a short press
	if (FollowTime <= ShortPressThreshold && canRun)
	{
		// We look for the location in the world where the player has pressed the input
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		HitLocation = Hit.Location;
		APawn* const MyPawn = GetPawn();
		HitLocation = CheckDistance(MyPawn->GetActorLocation(), HitLocation);
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitLocation);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, HitLocation, FRotator::ZeroRotator,
		                                               FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
		canRun = false;
		endTurn_Implementation();
	}
}

void ARPGPlayerController::OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = true;
	OnSetDestinationPressed();
}

void ARPGPlayerController::OnRightTouchPressed()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, true, Hit);
	if(Hit.GetActor())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(Hit.GetActor(),UHitable::StaticClass()))
		{
			evOnAttack.Broadcast(Hit.GetActor());
		}
	}
}

void ARPGPlayerController::OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

FVector ARPGPlayerController::CheckDistance(FVector playerPos, FVector destination)
{
	float distance = UKismetMathLibrary::Sqrt(
		(FMath::Pow(playerPos.X - destination.X, 2)
			+ FMath::Pow(playerPos.Y - destination.Y, 2) + FMath::Pow(
				playerPos.Z - destination.Z, 2)));


	if (distance > maxMoveDistance)
	{
		FVector dir = (destination - playerPos);
		FVector newpos = playerPos + dir.GetSafeNormal2D() * maxMoveDistance;
		return newpos;
		// UE_LOG(LogTemp, Display, TEXT("New Pos: %f %f %f"), newPos.X, newPos.Y, newPos.Z);
		// UE_LOG(LogTemp, Display, TEXT("Player Pos: %f %f %f"), playerPos.X, playerPos.Y, playerPos.Z);
		// return newPos;
	}
	else
	{
		return destination;
	}
}

void ARPGPlayerController::endTurn_Implementation()
{
	ITurnable::endTurn_Implementation();
	canAttack = false;
	canRun = false;
	gm->GiveNextTurn();
}

void ARPGPlayerController::startTurn_Implementation()
{
	ITurnable::startTurn_Implementation();
	canAttack = true;
	canRun = true;
}

void ARPGPlayerController::onHit_Implementation(int attack, int dmg)
{
	IHitable::onHit_Implementation(attack, dmg);
	if(attack >= ac)
	{
		hp-=dmg;
		if (hp<=0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Me muero"));
		}
	}
}





