// Fill out your copyright notice in the Description page of Project Settings.


#include "AlgoWidget.h"

#include "Algo_Comp3/AStarGraph.h"


UAlgoWidget::UAlgoWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
	
}

void UAlgoWidget::NativeConstruct()
{
	graph = Cast<AAStarGraph>(graph);
	if(graph == nullptr)
		return;
	
	if(DijkstraButton)
		DijkstraButton->OnClicked.AddDynamic(this, &UAlgoWidget::OnClickButtonDijkstra);

	if(TravelManButton)
		TravelManButton->OnClicked.AddDynamic(this, &UAlgoWidget::OnClickButtonTravelMan);

	if(AStarButton)
		AStarButton->OnClicked.AddDynamic(this, &UAlgoWidget::OnClickButtonAStar);



	
	
}


void UAlgoWidget::OnClickButtonDijkstra()
{
	if(graph == nullptr)
	{

		UE_LOG(LogTemp,Warning, TEXT("nullptr at OnClickButtonDijkstra "));
		return;
	}
	
	graph->DijkstraBoys();
	
	
}


void UAlgoWidget::OnClickButtonTravelMan()
{
	if(graph == nullptr)
	{

		UE_LOG(LogTemp,Warning, TEXT("nullptr at OnClickButtonTravelMan "));
		return;
	}
	
	graph->LonesomeTraveler();
	
}


void UAlgoWidget::OnClickButtonAStar()
{

	if(graph == nullptr)
	{

		UE_LOG(LogTemp,Warning, TEXT("nullptr at OnClickButtonAStar "));
		return;
	}
	
	graph->AStarSearch();
	
}




// void UAlgoWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
// {
// 	Super::NativeTick(MyGeometry, InDeltaTime);
//
//
//
// 	
// }