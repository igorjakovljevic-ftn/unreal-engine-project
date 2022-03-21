// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include "FPSPlayerController.h"

//We can use this class as a sort of container for anything we want to replicate from the GameMode class

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	//Figuring out which pawns are locally controlled so we can disable inputs on mission complete
	//This isnt very efficient if there are a lot of pawns in the world
	for (FConstPawnIterator it = GetWorld()->GetPawnIterator(); it; it++) {
		APawn* Pawn = it->Get();
		
		if(Pawn && Pawn->IsLocallyControlled()){
			Pawn->DisableInput(nullptr);
		}
	}

	for (FConstPlayerControllerIterator it = GetWorld()->GetPlayerControllerIterator(); it; it++) {
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(it->Get());

		if (PC && PC->IsLocalController()) {
			PC->OnMissionCompleted(InstigatorPawn, bMissionSuccess);
		}
	}
}
