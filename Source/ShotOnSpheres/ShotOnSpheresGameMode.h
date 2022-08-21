// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include <list>
#include "CustomSphere.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShotOnSpheresGameMode.generated.h"

UCLASS(minimalapi)
class AShotOnSpheresGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	std::list< ACustomSphere*> mySphere;
	//ACustomSphere* mySphere[15];
	int MAX = 15;
	float MAX_DISTANCE = 2000.0f;
public:
	AShotOnSpheresGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	//MY
	FVector RandomSphereLocation();
	FVector GetLocationMyCharater();
	void CreateListSpheres();
	void CheckSpheresCount();
};



