// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PuzzleGameMode.h"
#include "PuzzlePlayerController.h"
#include "PuzzlePawn.h"

APuzzleGameMode::APuzzleGameMode()
{
	// no pawn by default
	DefaultPawnClass = APuzzlePawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = APuzzlePlayerController::StaticClass();
}
