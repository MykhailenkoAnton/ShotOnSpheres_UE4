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

	//NY
	CreateListSpheres();
}


// random location Actor(Sphere) relatively Character
FVector AShotOnSpheresGameMode::RandomSphereLocation()
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

FVector AShotOnSpheresGameMode::GetLocationMyCharater()
{
	FVector Location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	return Location;
}

void AShotOnSpheresGameMode::CreateListSpheres()
{
	// get character location
	FVector myLocChar = GetLocationMyCharater();
	FRotator myRot(0, 0, 0);

	for (int i = 0; i < MAX; i++)
	{
		FVector LocationSphere;
		while (true)
		{
			LocationSphere = RandomSphereLocation();
			auto it = std::find_if(mySphere.begin(), mySphere.end(), [&LocationSphere](ACustomSphere* sphere) {

				return FVector::PointsAreNear(LocationSphere, sphere->GetLocSphere(), 80.0f);
				});

			if (it == mySphere.end())
			{
				break;
			}
			else
			{
				check(GEngine != nullptr);
				GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, TEXT("Sphere near, go next iteration"));
			}
		}
		
		check(GEngine != nullptr);
		FString mystr = LocationSphere.ToString() + " " + FString::FromInt(i);
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, mystr);

		
		auto Sphere = GetWorld()->SpawnActor<ACustomSphere>(ACustomSphere::StaticClass(), LocationSphere, myRot);
		Sphere->SetLocSphere(LocationSphere);
		mySphere.push_back(Sphere);
	}
}


void AShotOnSpheresGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AShotOnSpheresGameMode::CheckSpheresCount()
{
	int s = 0;
	for (auto i : mySphere)
	{
		if (i->IsActorBeingDestroyed())
		{
			s++;
		}
	}

	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::FromInt(s));

	if (s > 10)
	{
		for (auto i : mySphere)
		{
			i->Destroy();
			check(GEngine != nullptr);
			GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Orange, TEXT("CheckSpheresCount"));
		}

		GetWorld()->ForceGarbageCollection(true);
		mySphere.clear();
		CreateListSpheres();
	}

}