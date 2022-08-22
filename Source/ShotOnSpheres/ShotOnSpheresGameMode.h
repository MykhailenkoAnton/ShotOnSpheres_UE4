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

	// spheres objects. Ñhangeable.
	int MAX_SPHERES = 15;

	//Ñhangeable.
	float MAX_DISTANCE = 2000.0f;

	// wave count
	int wave_count = 1;
public:
	AShotOnSpheresGameMode();

	virtual void BeginPlay() override;

public:
	// random location Actor(Sphere) relatively Character
	FVector RandomSphereLocationRelativelyCharacter();

	// Create List spheres
	void CreateListSpheres();

	// random location Actor(Sphere) relatively another Spheres
	FVector LocationSphereRelativelySpheres();

	// incrementing wave_count on n
	void NumberOfWave(int n);

	// set wave's number
	void SetNumberWave(int n);

	// set maximum distance
	void SetUpMaxDistance(float max);

	//get maximum distance
	float GetMaxDistance();

	// Get My Actor(Player) Location 
	FVector GetLocationMyCharater();

	// Check how spheres remains and show wave's number
	void CheckSpheresCount();

	// Set MAX_SPHERES spheres on scene
	void SetUpMaxSpheres(float percent);

	// Get MAX_SPHERES spheres on scene
	int GetMaxSpheres();

	void SetMaxDistance(float max);

	void SetMaxSpheres(int n);
};



