// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarGraph.h"
#include "AStarNode.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAStarGraph::AAStarGraph()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	RootComponent = BoxComponent;

}

// Called when the game starts or when spawned
void AAStarGraph::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnSetAmountOfNodes();
	// SetUpEdges();
	CreateEdges();
	// SetNodeConnections();
	
}

// Called every frame
void AAStarGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//BoxScan();
	DrawEdges();

	// TestConnection(startNodeBoy, endNodeBoy);
	
}


void AAStarGraph::SpawnSetAmountOfNodes()
{
	// spawn the blueprint versions of starnodes
	if(starnodeBP)
	{
		
		int xAxis = 0;
		int yAxis = 1;
		for(int i = 0; i < 9; i++)
		{
			if(i % 3 == 0) { xAxis = 0;}
			if(i % 3 == 0) { yAxis +=1;}

			xAxis +=1;
			
			
			AAStarNode* newStar = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, FVector(xAxis * 1000.f,  yAxis * 1000.f, 100.f),FRotator::ZeroRotator);
			newStar->nodeID = i;
			StarNodeArray.Add(newStar);
		}


	}


	// Material
	for (int i = 0; i < StarNodeArray.Num(); i++)
	{

		int randomNum = FMath::RandRange(1,3);


		switch (randomNum)
		{
		case 1:
			StarNodeArray[i]->NodeMesh->SetMaterial(0, StarNodeArray[i]->NodeMaterialBlue);
			break;

		case 2:
			StarNodeArray[i]->NodeMesh->SetMaterial(0, StarNodeArray[i]->NodeMaterialGreen);
			break;
			
		case 3:
			StarNodeArray[i]->NodeMesh->SetMaterial(0, StarNodeArray[i]->NodeMaterialOrange);
			break;
		}
		
		
	}
	

	StarNodeArray[0]->NodeArrayConnections.Add(StarNodeArray[1]);
	StarNodeArray[0]->NodeArrayConnections.Add(StarNodeArray[3]);
	StarNodeArray[0]->NodeArrayConnections.Add(StarNodeArray[4]);
	
	StarNodeArray[1]->NodeArrayConnections.Add(StarNodeArray[0]);
	StarNodeArray[1]->NodeArrayConnections.Add(StarNodeArray[2]);
	StarNodeArray[1]->NodeArrayConnections.Add(StarNodeArray[3]);
	StarNodeArray[1]->NodeArrayConnections.Add(StarNodeArray[4]);
	StarNodeArray[1]->NodeArrayConnections.Add(StarNodeArray[5]);

	StarNodeArray[2]->NodeArrayConnections.Add(StarNodeArray[1]);
	StarNodeArray[2]->NodeArrayConnections.Add(StarNodeArray[4]);
	StarNodeArray[2]->NodeArrayConnections.Add(StarNodeArray[5]);

	StarNodeArray[3]->NodeArrayConnections.Add(StarNodeArray[0]);
	StarNodeArray[3]->NodeArrayConnections.Add(StarNodeArray[1]);
	StarNodeArray[3]->NodeArrayConnections.Add(StarNodeArray[4]);
	StarNodeArray[3]->NodeArrayConnections.Add(StarNodeArray[6]);
	StarNodeArray[3]->NodeArrayConnections.Add(StarNodeArray[7]);

	StarNodeArray[4]->NodeArrayConnections.Add(StarNodeArray[0]);
	StarNodeArray[4]->NodeArrayConnections.Add(StarNodeArray[1]);
	StarNodeArray[4]->NodeArrayConnections.Add(StarNodeArray[2]);
	StarNodeArray[4]->NodeArrayConnections.Add(StarNodeArray[3]);
	StarNodeArray[4]->NodeArrayConnections.Add(StarNodeArray[5]);
	StarNodeArray[4]->NodeArrayConnections.Add(StarNodeArray[6]);
	StarNodeArray[4]->NodeArrayConnections.Add(StarNodeArray[7]);
	StarNodeArray[4]->NodeArrayConnections.Add(StarNodeArray[8]);

	StarNodeArray[5]->NodeArrayConnections.Add(StarNodeArray[1]);
	StarNodeArray[5]->NodeArrayConnections.Add(StarNodeArray[2]);
	StarNodeArray[5]->NodeArrayConnections.Add(StarNodeArray[4]);
	StarNodeArray[5]->NodeArrayConnections.Add(StarNodeArray[7]);
	StarNodeArray[5]->NodeArrayConnections.Add(StarNodeArray[8]);

	StarNodeArray[6]->NodeArrayConnections.Add(StarNodeArray[3]);
	StarNodeArray[6]->NodeArrayConnections.Add(StarNodeArray[4]);
	StarNodeArray[6]->NodeArrayConnections.Add(StarNodeArray[7]);

	StarNodeArray[7]->NodeArrayConnections.Add(StarNodeArray[3]);
	StarNodeArray[7]->NodeArrayConnections.Add(StarNodeArray[4]);
	StarNodeArray[7]->NodeArrayConnections.Add(StarNodeArray[5]);
	StarNodeArray[7]->NodeArrayConnections.Add(StarNodeArray[6]);
	StarNodeArray[7]->NodeArrayConnections.Add(StarNodeArray[8]);


	StarNodeArray[8]->NodeArrayConnections.Add(StarNodeArray[4]);
	StarNodeArray[8]->NodeArrayConnections.Add(StarNodeArray[5]);
	StarNodeArray[8]->NodeArrayConnections.Add(StarNodeArray[7]);
	
}

void AAStarGraph::SetNodeConnections()
{
/*	WORK IN PROGRESS!	*/
	// for (int i = 0; i < StarNodeArray.Num()-5; i++)
	// {
	//
	// 	for (int j = 0; j < 2; j++)
	// 	{
	// 		StarNodeArray[i]->connections[j] = StarNodeArray[j+1];
	// 	}
	// 	
	// }


	
}

void AAStarGraph::CreateEdges()
{
	// std::priority_queue<FVector> nodedir;

	// FVector Dir = StarNodeArray[i]->NodeArrayConnections[j]->Node


	//TODO Enten reformatere kode eller fjerne
	// for (int i = 0; i < StarNodeArray.Num()-1; i++)
	// {
	// 	for (int j = 0; j < StarNodeArray[i]->NodeArrayConnections.Num(); j++)
	// 	{
	// 		DirectionPerConnection.Add(StarNodeArray[i]->NodeArrayConnections[j]->NodeLocation - StarNodeArray[i]->NodeLocation);
	//
	// 		UE_LOG(LogTemp,Warning,	TEXT("Dir %s"), *DirectionPerConnection[i].ToString());
	// 		
	//
	// 	}
	// }

	for (int i = 1; i < StarNodeArray.Num(); i++)
	{
		StarNodeArray[i]->Cost = StarNodeArray[i]->GetDistanceTo(StarNodeArray[0]);
	}
	
	
	
	

}

void AAStarGraph::DrawEdges()
{
	
	// for (int i = 0; i < StarNodeArray.Num()-1; i++)
	// {
	// 	DrawDebugLine(GetWorld(),StarNodeArray[i]->NodeLocation, StarNodeArray[i+1]->NodeLocation, FColor::Emerald, false, -1, 0, 5);
	// }


	for (int i = 0; i < StarNodeArray.Num()-1; i++)
	{

		for (int j = 0; j < StarNodeArray[i]->NodeArrayConnections.Num(); j++)
			DrawDebugLine(GetWorld(), StarNodeArray[i]->NodeLocation, StarNodeArray[i]->NodeArrayConnections[j]->NodeLocation, FColor::Emerald, false, -1, 0, 5);
	}
	
}

void AAStarGraph::TestConnection(class AAStarNode* start, class AAStarNode* end)
{

	//TODO CREATE EDGES -- or improve them~~~
	start = StarNodeArray[0];
	end = StarNodeArray[6];

	
	
	// FVector dist = start->NodeLocation;
	//
	// std::priority_queue<FVector> priorityQ_Vertex;
	//
	// for (int i = 0; i < StarNodeArray.Num(); i++)
	// {
	// 	for (int j = 0; j < StarNodeArray[i]->NodeArrayConnections.Num())
	// 		priorityQ_Vertex.emplace(StarNodeArray[i]->NodeArrayConnections[j]);
	// }




	

	// start = startNodeBoy;
	// end = endNodeBoy;

	// DrawDebugLine(GetWorld(),start->NodeLocation, end->NodeLocation,FColor::Emerald,false,-1,0,5);
	
	/*
	if(starnodeBP)
		AAStarNode * newStar = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, FVector(10.f,10.f,100.f), FRotator::ZeroRotator);
	*/
	
}

void AAStarGraph::SpawnStarNodes()
{
	for (int i = 0; i < 10; i++)
	{

		float newX = FMath::RandRange(0.f, 100.f);
		float newY = FMath::RandRange(0.f, 100.f);

		FVector nodeLocation = FVector(newX, newY, 1.f);
			
		if (starnodeBP == nullptr)
			return;

		// nodeBoy = GetWorld()->SpawnActor<
		//

	}
		


}

void AAStarGraph::Dijkstra(class AAStarGraph* graph, class AAStarNode* source)
{
	/*PSEUDO CODE FROM WIKI : // https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm 
	
			function Dijkstra(Graph, source):
			dist[source] ← 0                           // Initialization

			create vertex priority queue Q

			for each vertex v in Graph.Vertices:
				if v ≠ source
					dist[v] ← INFINITY                 // Unknown distance from source to v
					prev[v] ← UNDEFINED                // Predecessor of v

				Q.add_with_priority(v, dist[v])


			while Q is not empty:                      // The main loop
				u ← Q.extract_min()                    // Remove and return best vertex
				for each neighbor v of u:              // Go through all v neighbors of u
					alt ← dist[u] + Graph.Edges(u, v)
					if alt < dist[v]:
						dist[v] ← alt
						prev[v] ← u
						Q.decrease_priority(v, alt)

			return dist, prev
	*/


}

void AAStarGraph::TravelingSalesmanAlgorithm()
{

	std::vector<AAStarNode*> vertex;
	for (int i=1; i < StarNodeArray.Num(); i++)
	{
		vertex.push_back(StarNodeArray[i]);
	}

	int min_path = INT_MAX;

	do
	{
		// store current Path weight (cost)
		int current_pathweight = 0;

		// Compute current path weight
		int k = 0;
		
	}
	while (true);

	
	
	
}

void AAStarGraph::DijkstraBoys(class AAStarNode* start, class AAStarNode* end)
{
	// std::priority_queue<AAStarNode>	pq; // default: max-heap største på rot

	// acsending priority

	// std::priority_queue<>

}

float AAStarGraph::minDistance(float dist[], bool sptSet[]) 
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < AmountOfNodesToCreate; v++)
	{

		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	}
		return min_index;

}


