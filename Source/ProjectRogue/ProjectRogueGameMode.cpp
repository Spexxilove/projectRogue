// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectRogueGameMode.h"
#include "ProjectRoguePawn.h"

AProjectRogueGameMode::AProjectRogueGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AProjectRoguePawn::StaticClass();
}

