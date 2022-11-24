// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Algo_Comp3GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ALGO_COMP3_API AAlgo_Comp3GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AAlgo_Comp3GameModeBase();


	virtual void Tick(float DeltaSeconds) override;
	
	
};
