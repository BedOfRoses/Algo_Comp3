// Fill out your copyright notice in the Description page of Project Settings.


#include "AlgoHUD.h"
#include "GraphAStar.h"
#include "Algo_Comp3/AStarGraph.h"
#include "Algo_Comp3/AStarNode.h"

AAlgoHUD::AAlgoHUD()
{
	
}

void AAlgoHUD::DrawHUD()
{
	Super::DrawHUD();
	
}

void AAlgoHUD::BeginPlay()
{




	
	if(HUDWidgetClass)
	{
		AlgoWidget = CreateWidget<UAlgoWidget>(GetWorld(), HUDWidgetClass);
		AlgoWidget->AddToViewport();
	}


	
	Super::BeginPlay();
}



void AAlgoHUD::ExecuteDijsktra()
{
	// AAStarGraph* graph = Cast<AAStarGraph>(AHUD, GetWorld()->GetFirstPlayerController()->GetHUD());
	// AAStarGraph* StarGraph = Cast<AAStarGraph>(GetWorld()->GetFirstPlayerController()->getpl);
	
}

void AAlgoHUD::ExecuteTravelMan()
{
	
}

