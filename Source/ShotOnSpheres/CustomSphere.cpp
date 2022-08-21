// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomSphere.h"	
#include <string>


// Sets default values
ACustomSphere::ACustomSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(SphereVisualAsset.Object);
		
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> SphereMateriallAsset(TEXT("/Game/StarterContent/Props/Materials/M_Chair"));
	if (SphereMateriallAsset.Succeeded())
	{
		VisualMesh->SetMaterial(0, SphereMateriallAsset.Object);
	}


	/*std::string str;
	str = std::to_string(Amount_Spheres);
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Orange, str.c_str());*/

	/*check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Orange, TEXT("CONSTRUCTOR"));*/

}

ACustomSphere::~ACustomSphere()
{
	/*std::string str;
	str = std::to_string(Amount_Spheres);
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Orange, str.c_str()); */
	/*check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Orange, TEXT("DESTRUCTOR"));*/
}

// Called when the game starts or when spawned
void ACustomSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACustomSphere::SetLocSphere(FVector location)
{
	UniqLocation = location;
}

FVector ACustomSphere::GetLocSphere()
{
	return UniqLocation;
}