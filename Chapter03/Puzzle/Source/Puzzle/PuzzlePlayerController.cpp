// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PuzzlePlayerController.h"

APuzzlePlayerController::APuzzlePlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
