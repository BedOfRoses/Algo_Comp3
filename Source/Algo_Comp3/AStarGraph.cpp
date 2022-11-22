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



	
	CreateEdges();
	// DrawEdges();
	
	
	 DijkstraBoys();
}

// Called every frame
void AAStarGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
	//BoxScan();
	// DrawEdges();

	//DijkstraBoys();
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

/* WIP, FOR DYNAMIC SIZE OF NODES*/
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

	//for (int i = 0; i < StarNodeArray.Num()-1; i++)
	for (int i = 0; i < StarNodeArray.Num(); i++)
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




void AAStarGraph::DijkstraBoys() // class AAStarNode* start, class AAStarNode* end
{

	//init

	for (int i = 0; i < StarNodeArray.Num(); i++)
	{
		StarNodeArray[i]->DistFromStart = INT_MAX;
		StarNodeArray[i]->bVisited = false;
	}

	AAStarNode* StartNode = StarNodeArray[0];
	AAStarNode* EndNode = StarNodeArray[8];

	if(!StartNode)
		return;
	if(!EndNode)
		return;

	StartNode->DistFromStart = 0.f;

	int ctrEX = 0;

	AAStarNode* current = StartNode;
	if(!current)
		return;


	
	while (EndNode->bVisited == false || ctrEX <= 2)
	{
		

		// checking all nodes from current's neighbours
		for (int i = 0; i < current->NodeArrayConnections.Num(); i++)
		{
			if(current->NodeArrayConnections[i]->bVisited == false)
			{
				float distance = current->NodeArrayConnections[i]->GetDistanceTo(current);

				float totalcost = distance + current->DistFromStart;

				if(totalcost < current->NodeArrayConnections[i]->DistFromStart)
				{
					current->NodeArrayConnections[i]->DistFromStart = totalcost;
					current->NodeArrayConnections[i]->PrevStarNode = current;	
				}

				StarNodeMap.Emplace(current->NodeArrayConnections[i]->DistFromStart, current->NodeArrayConnections[i]);

				DrawDebugLine(GetWorld(), current->NodeLocation,
				current->NodeArrayConnections[i]->NodeLocation, FColor::Green,
				false, 0.5, 0, 10);
			
			}
		}

		//sort the TMap

		if(StarNodeMap.begin())
		{
			StarNodeMap.KeySort([](float A, float B){return A <B;});
			Cheapest = StarNodeMap.begin().Value();
			current = Cheapest;
			StarNodeMap.Remove(StarNodeMap.begin().Key());
		}
		
		current->bVisited = true;
	

		AAStarNode* temp = EndNode;
		while (temp->PrevStarNode != nullptr)
		{
			DrawDebugLine(GetWorld(), temp->NodeLocation,
				temp->PrevStarNode->NodeLocation, FColor::Green, true, -1, 0, 10);
			
			temp = temp->PrevStarNode;
		}
		


		ctrEX++;
	}
	

}

float AAStarGraph::minDistance(float dist[], bool sptSet[]) 
{
	int min = INT_MAX, min_index{};

	for (int v = 0; v < AmountOfNodesToCreate; v++)
	{

		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	}
		return min_index;

}









/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
// 	// initialize start and end
//
// 	 AAStarNode* Start = nullptr;
// 	 AAStarNode * End = nullptr;;
//
// 	Start = StarNodeArray[0];
// 	End = StarNodeArray[8];
//
// 	if(Start==nullptr)
// 		return;
//
// 	if(End == nullptr)
// 		return;
//
// 	for	(int a = 0; a < StarNodeArray.Num(); a++)
// 	{
// 		StarNodeArray[a]->bVisited = false;
// 		StarNodeArray[a]->DistFromStart = INT_MAX;
// 	}
//
// 	Start->bVisited = true;
// 	End->bVisited = false;
// 	
// 	AAStarNode* current = Start;
//
// 	current->PrevStarNode = nullptr;
// 	current->bVisited = true;
// 	TArray<AAStarNode*> pathArray;
//
// 	
// 	// add start paths to path array
// 	// set nodes to visited
//
// 	// while !array.empty()
// 	// sort paths array on cost of path
// 	// get shortest path
// 	// pop shortest path from array
//
// 	// for nodes in path.endnode.edges
// 	// add new paths from shortest paths end node and set those nodes to visited (old + new path cost)
// 	// if node on path end is end node: break
// 	// loop again
// 	
// 	for (int i = 0; i < StarNodeArray.Num(); i++)
// 		for (int j = 0; j < StarNodeArray[i]->NodeArrayConnections.Num(); j++)
// 		{
//
// 			// edges.Add(StarNodeArray[i]->NodeArrayConnections[j]);
//
// 			
// 			// StarNodeMap.Emplace(StarNodeArray[i]->NodeArrayConnections[j]->DistFromStart, StarNodeArray[i]->NodeArrayConnections[j]);
// 			
// 			/*
// 			if(current->NodeArrayConnections[j] && current->NodeArrayConnections[j]->bVisited != true)
// 			{
// 				float cost = current->Cost;
// 				float dist = current->GetDistanceTo(current->NodeArrayConnections[j]);
//
// 				float totcost = cost + dist + current->DistFromStart;
//
// 				if(totcost < current->DistFromStart)
// 				{
// 					current->NodeArrayConnections[j]->DistFromStart = totcost;
// 					current->NodeArrayConnections[j]->PrevStarNode = current;
// 				}
// 				StarNodeMap.Emplace(current->NodeArrayConnections[j]->DistFromStart, current->NodeArrayConnections[j]);
// 				DrawDebugLine(GetWorld(), current->NodeLocation, current->NodeArrayConnections[j]->NodeLocation,
// 					FColor::Red, true, -1, 0, 5);
// 				
// 			}
// 			*/
// 			
//
//
// 			
// 		}
// 	
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////





// HALDOR VERSION
// OUR STARTING AND ENDING POINTERS
	// AAStarNode* start = StarNodeArray[0];
	// AAStarNode* end = StarNodeArray[8];
	//
	// UE_LOG(LogTemp, Warning, TEXT("AAStarNode* start = StarNodeArray[0]"));
	// UE_LOG(LogTemp, Warning, TEXT("AAStarNode* end = StarNodeArray[8];"));
	//
	// /*	END IF THERE IS NOTHING	*/
	// if (start == nullptr)
	// 	return;
	// if(end == nullptr)
	// 	return;
	//
	// /* Iterate through the array and set the distance from start to max	*/
	// for (int i = 0; i < StarNodeArray.Num(); i++)
	// {
	// 	StarNodeArray[i]->DistFromStart = INT_MAX;
	// 	StarNodeArray[i]->bVisited = false;
	// 	UE_LOG(LogTemp, Warning, TEXT("StarNodeArray[i]->DistFromStart"));
	// 	UE_LOG(LogTemp, Warning, TEXT("StarNodeArray[i]->bVisited = false;"));
	// }
	//
	// // OUR STARTING NODE IS THE ONE THAT WE START VISITING
	// // ALSO ITS DISTANCE FROM ITSELF IS 0
	// start->DistFromStart = 0.f;
	// start->bVisited = true;
	// end->bVisited = false;
	//
	// // CREATE A POINTER THAT WILL BE OUR CURRENT-NODE-POINTER
	// class AAStarNode* curr = start;
	//
	// // NO PREVIOUS ON STARTING NODE
	// if(curr == start)
	// {
	// 	curr->PrevStarNode = nullptr;
	// 	UE_LOG(LogTemp, Warning, TEXT("curr->PrevStarNode = nullptr;"));
	// }


	



/*
	while (end->bVisited == false)
	{

		//check all close nodes for their COST and DISTANCE
		for (int i = 0; i < StarNodeArray.Num(); i++)
		{

			for (int j = 0; j < StarNodeArray[i]->NodeArrayConnections.Num(); j++)
			{
				// DrawDebugLine(GetWorld(), StarNodeArray[i]->NodeLocation, StarNodeArray[i]->NodeArrayConnections[j]->NodeLocation, FColor::Emerald, false, -1, 0, 5);

				if (StarNodeArray[i]->NodeArrayConnections[j]->bVisited != true)
				{
					float cost = curr->Cost;
					float dist = curr->GetDistanceTo(StarNodeArray[i]->NodeArrayConnections[j]);

					float TotCost = cost + dist + curr->DistFromStart;

					if(TotCost < curr->DistFromStart)
					{
						curr->DistFromStart = TotCost;
						curr->PrevStarNode = curr;
						
					}
					StarNodeMap.Emplace(curr->DistFromStart, curr);
					DrawDebugLine(GetWorld(), curr->NodeLocation,
						StarNodeArray[i]->NodeArrayConnections[j]->NodeLocation,
						FColor::Red, true, -1, 0, 4);

					
				}
				

			}
			
			// if(StarNodeMap.begin())
   //          		{
   //          			StarNodeMap.KeySort([](float A, float B){return A < B;});
   //          			Cheapest = StarNodeMap.begin().Value();
   //          			curr = Cheapest;
   //          			StarNodeMap.Remove(StarNodeMap.begin().Key());
   //          		}
   //          		curr->bVisited = true;
		}

		// AAStarNode* temp = end;
		//
		// while (end->PrevStarNode !=nullptr)
		// {
		// 		DrawDebugLine(GetWorld(), temp->NodeLocation, temp->PrevStarNode->NodeLocation, FColor::Red, true, -1, 0 ,10);
		// 		temp = temp->PrevStarNode;
		// 	
		// }

		

		
		
	}
*/	

