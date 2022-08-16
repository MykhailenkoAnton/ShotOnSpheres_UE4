// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomSphere.h"

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
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Orange, TEXT("CONSTRUCTOR"));

}

ACustomSphere::~ACustomSphere()
{
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Orange, TEXT("DESTRUCTOR"));
}

// Called when the game starts or when spawned
void ACustomSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

