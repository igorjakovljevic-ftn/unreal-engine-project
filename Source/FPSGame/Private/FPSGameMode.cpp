// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameState.h"

//GameMode cannot be replicated to the clients which is why networking here has to be done differently (via GameState class)

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	//Setting the game state for this specific game mode
	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn) {

		if (SpectatingViewpointClass) {
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			if (ReturnedActors.Num() > 0) {
				AActor* NewViewTarget = ReturnedActors[0];

				for (FConstPlayerControllerIterator it = GetWorld()->GetPlayerControllerIterator(); it; it++) {
					APlayerController* PC = it->Get();
					
					if (PC) {
						PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
					}
				}
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is null. Cannot change spectating view target."))
		}
	}

	AFPSGameState* GS = GetGameState<AFPSGameState>();
	if (GS) {
		GS->MulticastOnMissionComplete(InstigatorPawn, bMissionSuccess);
	}

	//Blueprint function call
	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
}

