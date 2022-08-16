// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CustomSphere.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShotOnSpheresGameMode.generated.h"

UCLASS(minimalapi)
class AShotOnSpheresGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:


public:
	AShotOnSpheresGameMode();

	virtual void StartPlay() override;
	FVector RandomLocation();
};



