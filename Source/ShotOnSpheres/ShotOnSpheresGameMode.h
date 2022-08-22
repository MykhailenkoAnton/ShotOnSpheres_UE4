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
	// list me Actors
	std::list< ACustomSphere*> MySpheres_;

	// spheres objects. Ñhangeable.
	int MaxSpheres_ = 15;

	//Ñhangeable.
	float MaxDistance_ = 2000.0f;

	// wave count
	int WaveCount_ = 1;
public:
	AShotOnSpheresGameMode();

	virtual void BeginPlay() override;

public:
	// random location Actor(Sphere) relatively Character
	FVector RandomSphereLocationRelativelyCharacter();

	// Create List spheres
	void CreateListSpheres();

	// random location Actor(Sphere) relatively another Spheres
	FVector CheckLocationSphereRelativelySpheres();

	// incrementing wave_count on n
	void NumberOfWave(int n);

	// set wave's number
	void SetNumberWave(int n);

	// set UP maximum distance. Add amount in % to MAX_DISTANCE
	void SetUpMaxDistance(float percent);

	//get maximum distance
	float GetMaxDistance();

	// Get My Actor(Player) Location 
	FVector GetLocationMyCharater();

	// Check how spheres remains and show wave's number
	void CheckSpheresCount();

	// Set UP MAX_SPHERES spheres on scene. Add amount in % to MAX_SPHERES
	void SetUpMaxSpheres(float percent);

	// Get MAX_SPHERES spheres on scene
	int GetMaxSpheres();

	//Set max distance
	void SetMaxDistance(float max);

	//Set max spheres
	void SetMaxSpheres(int n);
};



