// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "Engine/Engine.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShotOnSpheresHUD.generated.h"

UCLASS()
class AShotOnSpheresHUD : public AHUD
{
	GENERATED_BODY()

public:
	AShotOnSpheresHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

