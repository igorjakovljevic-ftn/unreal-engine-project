// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameState.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	//if a NetMulticast function is called on the server it will also be sent to all the clients
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnMissionComplete(APawn* InstigatorPawn, bool bMissionSuccess);
};
