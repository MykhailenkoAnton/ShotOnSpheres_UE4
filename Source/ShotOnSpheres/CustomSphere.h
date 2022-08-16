// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/Engine.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomSphere.generated.h"

UCLASS()
class SHOTONSPHERES_API ACustomSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomSphere();
	~ACustomSphere();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// MyMesh
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;
};
