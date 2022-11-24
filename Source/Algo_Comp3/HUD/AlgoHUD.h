// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AlgoWidget.h"
#include "GameFramework/HUD.h"
#include "AlgoHUD.generated.h"

/**
 * 
 */
UCLASS()
class ALGO_COMP3_API AAlgoHUD : public AHUD
{
	GENERATED_BODY()

public:
	AAlgoHUD();

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category = "Algorithms")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UAlgoWidget* AlgoWidget = nullptr;


	virtual void Tick(float DeltaSeconds) override;


	
	
};
