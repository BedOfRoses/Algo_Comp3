// Fill out your copyright notice in the Description page of Project Settings.


#include "AlgoWidget.h"

#include "Algo_Comp3/AStarGraph.h"
#include "Kismet/GameplayStatics.h"


UAlgoWidget::UAlgoWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
	
}

void UAlgoWidget::NativeConstruct()
{

	UWorld* World = GetWorld();
	if (World)
	{
		AStarGraph = GetWorld()->SpawnActor<AAStarGraph>(StarGraphActorClass, FVector(0,0,0),
			FRotator::ZeroRotator);

	}

	//TODO CHECK OUT HOW TO CAST FOR REAL :)
	
	if(DijkstraButton)
	{
		DijkstraButton->OnClicked.AddDynamic(this, &UAlgoWidget::OnClickButtonDijkstra);
		UE_LOG(LogTemp, Warning, TEXT("DijkstraButton"));
	}
	if(TravelManButton)
	{
		TravelManButton->OnClicked.AddDynamic(this, &UAlgoWidget::OnClickButtonTravelMan);
		UE_LOG(LogTemp, Warning, TEXT("TravelManButton"));
	}

	if(AStarButton)
	{
		AStarButton->OnClicked.AddDynamic(this, &UAlgoWidget::OnClickButtonAStar);
		UE_LOG(LogTemp, Warning, TEXT("AStarButton"));
		
	}

	if(ResetButton)
	{
		ResetButton->OnClicked.AddDynamic(this, &UAlgoWidget::OnClickButtonReset);
		UE_LOG(LogTemp, Warning, TEXT("AStarButton"));
		
	}




	
	
}







void UAlgoWidget::OnClickButtonDijkstra()
{
	if(AStarGraph)
		AStarGraph->Run_Dijkstra();
	
	UE_LOG(LogTemp,Warning, TEXT("OnClickButtonDijkstra was clicked"));
	
}


void UAlgoWidget::OnClickButtonTravelMan()
{

	if(AStarGraph)
		AStarGraph->Run_TSP();

	

	UE_LOG(LogTemp,Warning, TEXT("OnClickButtonTravelMan"));
}


void UAlgoWidget::OnClickButtonAStar()
{
	if(AStarGraph)
		AStarGraph->Run_AStar();
	
	
	UE_LOG(LogTemp,Warning, TEXT("OnClickButtonAStar"));
	
}


void UAlgoWidget::OnClickButtonReset()
{
	UGameplayStatics::OpenLevel(this, "Gaming");
}




