// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include <string>
#include "ShotOnSpheresGameMode.h"
#include "ShotOnSpheresHUD.h"
#include "ShotOnSpheresCharacter.h"
#include "Engine/Engine.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/ConstructorHelpers.h"

AShotOnSpheresGameMode::AShotOnSpheresGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShotOnSpheresHUD::StaticClass();
}

void AShotOnSpheresGameMode::StartPlay()
{
	Super::StartPlay();

	CreateListSpheres();	
}

FVector AShotOnSpheresGameMode::RandomSphereLocation()
{

	FVector myLocChar = GetLocationMyCharater();

	FVector randomLoc;
	float MAX_DISTANCE = 2000.0f;
	float distance = FMath::FRandRange(0.0f, MAX_DISTANCE);

	randomLoc.Z = FMath::FRandRange(0.0f, distance);
	distance -= randomLoc.Z;

	randomLoc.X = FMath::FRandRange(-(distance), distance);
	bool IsAboveZero = randomLoc.X >= 0;
	if (IsAboveZero)
	{
		distance -= randomLoc.X;
	}
	else
	{
		distance += randomLoc.X;
	}

	auto temp = FMath::RandRange(-1, 1);
	randomLoc.Y = (temp >= 0) ? distance : -(distance);

	// random location Actor(Sphere) relatively Character
	randomLoc.Z += myLocChar.Z;

	auto rand = FMath::RandRange(-1, 1);
	(rand >= 0) ? randomLoc.X += myLocChar.X : randomLoc.X -= myLocChar.X;

	rand = FMath::RandRange(-1, 1);
	(rand >= 0) ? randomLoc.Y += myLocChar.Y : randomLoc.Y -= myLocChar.Y;

	return randomLoc;
}

FVector AShotOnSpheresGameMode::GetLocationMyCharater()
{
	FVector Location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	return Location;
}

void AShotOnSpheresGameMode::CreateListSpheres()
{
	// get character location
	int MAX = 15;
	FVector myLocChar = GetLocationMyCharater();

	FActorSpawnParameters SpawnInfo;
	FRotator myRot(0, 0, 0);

	for (int i = 0; i < MAX; i++)
	{
		FVector myLoc = RandomSphereLocation();

		if (myLocChar == myLoc)
		{
			while (myLocChar != myLoc)
			{
				myLoc = RandomSphereLocation();
			}
		}
		check(GEngine != nullptr);
		FString mystr = myLoc.ToString() + " " + FString::FromInt(i);
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, mystr);
		mySphere.push_back(GetWorld()->SpawnActor<ACustomSphere>(ACustomSphere::StaticClass(), myLoc, myRot, SpawnInfo));
	}
}