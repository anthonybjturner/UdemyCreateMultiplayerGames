// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "FPSPlayerController.h"

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* Instigator, bool bMissionSuccess){


	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++) {//Loops through all pawn controllers in the level

		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());
		if (PC && PC->IsLocalController()) {

			PC->OnMissionCompleted(Instigator, bMissionSuccess);
			APawn* MyPawn = PC->GetPawn();
			if (MyPawn) {

				MyPawn->DisableInput(nullptr);
			}
		}
	}
}
