// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ShotOnSpheresGameMode.h"
#include <string>
#include "ShotOnSpheresHUD.h"
#include "ShotOnSpheresCharacter.h"
#include "Engine/Engine.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/ConstructorHelpers.h"

AShotOnSpheresGameMode::AShotOnSpheresGameMode()
	: Super()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShotOnSpheresHUD::StaticClass();	
}


void AShotOnSpheresGameMode::BeginPlay()
{
	Super::BeginPlay();

	CreateListSpheres();
}


// random location Actor(Sphere) relatively Character
FVector AShotOnSpheresGameMode::RandomSphereLocationRelativelyCharacter()
{

	FVector randomLoc;
	FVector myLocChar = GetLocationMyCharater();

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

	
	randomLoc.Z += myLocChar.Z;

	auto rand = FMath::RandRange(-1, 1);
	(rand >= 0) ? randomLoc.X += myLocChar.X : randomLoc.X -= myLocChar.X;

	rand = FMath::RandRange(-1, 1);
	(rand >= 0) ? randomLoc.Y += myLocChar.Y : randomLoc.Y -= myLocChar.Y;

	return randomLoc;
}

// Get My Actor(Player) Location 
FVector AShotOnSpheresGameMode::GetLocationMyCharater()
{
	FVector Location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	return Location;
}

// Create List spheres and save location every spehere
void AShotOnSpheresGameMode::CreateListSpheres()
{
	FVector myLocChar = GetLocationMyCharater();
	FRotator myRot(0, 0, 0);

	// display MAX_SPHERES
	FString str = "Now MAX_SPHERES: ";
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, str + FString::Printf(TEXT("%d"), MAX_SPHERES));

	for (int i = 0; i < MAX_SPHERES; i++)
	{
		FVector LocationSphere = LocationSphereRelativelySpheres();
		
		// displays location spheres
		check(GEngine != nullptr);
		FString str = "Sphere location: ";
		FString mystr = LocationSphere.ToString() + " " + FString::FromInt(i);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, str + mystr);

		
		auto Sphere = GetWorld()->SpawnActor<ACustomSphere>(ACustomSphere::StaticClass(), LocationSphere, myRot);
		Sphere->SetLocSphere(LocationSphere);
		mySphere.push_back(Sphere);
	}
	NumberOfWave(1);
}

// random location Actor(Sphere) relatively another Spheres
FVector AShotOnSpheresGameMode::LocationSphereRelativelySpheres()
{
	FVector LocationSphere;
	while (true)
	{
		LocationSphere = RandomSphereLocationRelativelyCharacter();
		auto it = std::find_if(mySphere.begin(), mySphere.end(), [&LocationSphere](ACustomSphere* sphere) {

			return FVector::PointsAreNear(LocationSphere, sphere->GetLocSphere(), sphere->GetSimpleCollisionRadius() + 80.0f);
			});

		if (it == mySphere.end())
		{
			break;
		}
		else
		{
			//display location sphere, if distance < 80
			check(GEngine != nullptr);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Sphere near, go next iteration"));
		}
	}
	return LocationSphere;
}

// Check how many spheres remains
void AShotOnSpheresGameMode::CheckSpheresCount()
{
	int countSpheres = 1;
	for (auto i : mySphere)
	{
		if (i->IsActorBeingDestroyed())
		{
			countSpheres++;
		}
	}

	// display count spheres
	FString str = "Destroy spheres: ";
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, str + FString::FromInt(countSpheres));

	if (countSpheres > 10)
	{
		for (auto i : mySphere)
		{
			i->Destroy();
		}

		GetWorld()->ForceGarbageCollection(true);
		mySphere.clear();
		SetUpMaxSpheres(0.10f);
		SetUpMaxDistance(0.05f);
		CreateListSpheres();
	}
}

// incrementing wave_count on n
void AShotOnSpheresGameMode::NumberOfWave(int n)
{
	FString str = "WAVE #: ";
	// display wave's number
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, str +  FString::FromInt(wave_count));
	SetNumberWave(n);
}

// set wave's number
void AShotOnSpheresGameMode::SetNumberWave(int n)
{
	wave_count += n;
}

// set maximum distance in %
void AShotOnSpheresGameMode::SetUpMaxDistance(float percent)
{
	float temp = MAX_DISTANCE * percent;
	MAX_DISTANCE += temp;

	// display distance every wave
	FString str = "Now MAX_DISTANCE = ";
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, str + FString::Printf(TEXT("%f"), MAX_DISTANCE));
}

//get maximum distance
float AShotOnSpheresGameMode::GetMaxDistance()
{
	return MAX_DISTANCE;
}

// Set MAX_SPHERES spheres on scene
void AShotOnSpheresGameMode::SetUpMaxSpheres(float percent)
{
	float temp = MAX_SPHERES * percent;
	static_cast<int>(MAX_SPHERES += temp);
}

void AShotOnSpheresGameMode::SetMaxDistance(float max)
{
	MAX_DISTANCE = max;
}

void AShotOnSpheresGameMode::SetMaxSpheres(int n)
{
	MAX_SPHERES = n;
}

// Get MAX_SPHERES spheres on scene
int AShotOnSpheresGameMode::GetMaxSpheres()
{
	return MAX_SPHERES;
}

