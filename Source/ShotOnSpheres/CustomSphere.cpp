// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomSphere.h"	
#include <string>


// Sets default values
ACustomSphere::ACustomSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	VisualMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh_->SetupAttachment(RootComponent);
	
	//set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		VisualMesh_->SetStaticMesh(SphereVisualAsset.Object);
		
	}

	//set material
	static ConstructorHelpers::FObjectFinder<UMaterial> SphereMateriallAsset(TEXT("/Game/StarterContent/Props/Materials/M_Chair"));
	if (SphereMateriallAsset.Succeeded())
	{
		VisualMesh_->SetMaterial(0, SphereMateriallAsset.Object);
	}

}

// to see when destructor will be called
ACustomSphere::~ACustomSphere()
{
}

// Called when the game starts or when spawned
void ACustomSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

//set location for this sphere
void ACustomSphere::SetLocSphere(FVector location)
{
	UniqLocation_ = location;
}

//get location this sphere
FVector ACustomSphere::GetLocSphere()
{
	return UniqLocation_;
}