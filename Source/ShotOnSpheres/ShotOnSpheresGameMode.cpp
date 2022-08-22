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

	float distance = FMath::FRandRange(0.0f, MaxDistance_);

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
	FRotator MyRot(0, 0, 0);

	float temp = MaxDistance_;

	// display amount spheres every wave
	FString str = "NOW SPHERES: ";
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, str + FString::FromInt(MaxSpheres_));

	// display MaxDistance_ every wave
	FString str1 = "NOW DISTANCE: ";
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, str1 + FString::Printf(TEXT("%f"), MaxDistance_));

	// spawn sphere
	for (int i = 0; i < MaxSpheres_; i++)
	{
		// spawn 10 spheres in 1500 distance
		if (i < 10)
		{
			SetMaxDistance(1500.0f);
		}
		else
		{
			// else spawn on MaxDistance_
			SetMaxDistance(temp);
		}

		FVector LocationSphere = CheckLocationSphereRelativelySpheres();
		auto Sphere = GetWorld()->SpawnActor<ACustomSphere>(ACustomSphere::StaticClass(), LocationSphere, MyRot);
		Sphere->SetLocSphere(LocationSphere);
		MySpheres_.push_back(Sphere);
	}
	NumberOfWave(1);
}

// random location Actor(Sphere) relatively another Spheres
FVector AShotOnSpheresGameMode::CheckLocationSphereRelativelySpheres()
{
	FVector LocationSphere;
	while (true)
	{
		LocationSphere = RandomSphereLocationRelativelyCharacter();
		auto it = std::find_if(MySpheres_.begin(), MySpheres_.end(), [&LocationSphere](ACustomSphere* sphere) {

			return FVector::PointsAreNear(LocationSphere, sphere->GetLocSphere(), sphere->GetSimpleCollisionRadius() + 80.0f);
			});

		if (it == MySpheres_.end())
		{
			break;
		}
		else
		{
			//display location sphere, if distance < 80
			check(GEngine != nullptr);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Sphere near, go next iteration what would generate new location"));
		}
	}
	return LocationSphere;
}

// Check how many spheres remains
void AShotOnSpheresGameMode::CheckSpheresCount()
{
	int CountSpheres = 1;
	for (auto i : MySpheres_)
	{
		if (i->IsActorBeingDestroyed())
		{
			CountSpheres++;
		}
	}

	// display count spheres
	FString str = "Destroy spheres: ";
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, str + FString::FromInt(CountSpheres));

	if (CountSpheres > 10)
	{
		for (auto i : MySpheres_)
		{
			i->Destroy();
		}

		GetWorld()->ForceGarbageCollection(true);
		MySpheres_.clear();
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, str +  FString::FromInt(WaveCount_));
	SetNumberWave(n);
}

// set wave's number
void AShotOnSpheresGameMode::SetNumberWave(int n)
{
	WaveCount_ += n;
}

// set UP maximum distance. Add amount in % to MaxDistance_
void AShotOnSpheresGameMode::SetUpMaxDistance(float percent)
{
	float temp = MaxDistance_ * percent;
	MaxDistance_ += temp;
}

//get maximum distance
float AShotOnSpheresGameMode::GetMaxDistance()
{
	return MaxDistance_;
}

// Set UP MaxSpheres_ spheres on scene. Add amount in % to MaxSpheres_
void AShotOnSpheresGameMode::SetUpMaxSpheres(float percent)
{
	float temp = MaxSpheres_ * percent;
	static_cast<int>(MaxSpheres_ += temp);
}

void AShotOnSpheresGameMode::SetMaxDistance(float max)
{
	MaxDistance_ = max;
}

void AShotOnSpheresGameMode::SetMaxSpheres(int n)
{
	MaxSpheres_ = n;
}

// Get MAX_SPHERES spheres on scene
int AShotOnSpheresGameMode::GetMaxSpheres()
{
	return MaxSpheres_;
}

