// Fill out your copyright notice in the Description page of Project Settings.


#include "AlgoHUD.h"
#include "GraphAStar.h"
#include "Algo_Comp3/AStarGraph.h"
#include "Algo_Comp3/AStarNode.h"
#include "Kismet/GameplayStatics.h"

AAlgoHUD::AAlgoHUD()
{
	
}

void AAlgoHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	// AAStarGraph* graph = Cast<AAStarGraph>(AActor::GetOwner());
	
}


void AAlgoHUD::DrawHUD()
{
	Super::DrawHUD();
	
}

void AAlgoHUD::BeginPlay()
{
	Super::BeginPlay();


	FInputModeGameAndUI UI_Input;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	UI_Input.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(UI_Input);


	
	if(HUDWidgetClass)
	{
		AlgoWidget = CreateWidget<UAlgoWidget>(GetWorld(), HUDWidgetClass);
		AlgoWidget->AddToViewport();
	}


	
}
