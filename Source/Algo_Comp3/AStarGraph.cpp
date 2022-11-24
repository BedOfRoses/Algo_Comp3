// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarGraph.h"
#include "AStarNode.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "MathUtil.h"

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
	
	// // SpawnSetAmountOfNodes();
	//
	// randomSpawner();
	//
	// setDynamicEdges();
	//
	// // CreateEdges();
	//
	// DrawEdges();
	//  // DijkstraBoys();
	// // LonesomeTraveler();
	//
	// // AStarSearch();
	
}


// Called every frame
void AAStarGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

/*not in use*/
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
			DrawDebugLine(GetWorld(), StarNodeArray[i]->NodeLocation,
				StarNodeArray[i]->NodeArrayConnections[j]->NodeLocation,
				FColor::Silver, true, -1, 0, 5);
	}
	
}


void AAStarGraph::LonesomeTraveler()
{

	/*
	 * Klargjøre et array av alle noder bortsett fra kildenode ( den som sist besøkes igjen)
	 *
	 * ting som skal passes på: billigst rute, ikke gå en vei vi har gått før.
	 */
/*//init
	int sourceNumber = 0;
	AAStarNode* SourceNode = StarNodeArray[sourceNumber];
	if (SourceNode == nullptr)
		return;

	TArray<AAStarNode*> TravelManArray;

	for (int i = 0; i < StarNodeArray.Num(); i++)
	{
		if(i != sourceNumber)
		{
			StarNodeArray[i]->DistFromStart = INT_MAX;
			StarNodeArray[i]->bVisited = false;
			TravelManArray.Add(StarNodeArray[i]);
		}
	}
	
	AAStarNode* CurrentNode = SourceNode;
	if (CurrentNode == nullptr)
		return;*/



	for (int i = 0; i < StarNodeArray.Num(); i++)
	{
		StarNodeArray[i]->bVisited = false;
	}

	int endnum = StarNodeArray.Num();
	int rng = FMath::RandRange(0,endnum);

	AAStarNode* Source = StarNodeArray[rng];

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("rng: %d"), rng));	

	AAStarNode* current = Source;
	
	bool ikkjeBesokt = false;
	int getUsOut = 0;
	while (ikkjeBesokt == false || getUsOut <= 10000)
	{
	
		UE_LOG(LogTemp, Warning, TEXT("start"));

		// current->bVisited = true;
		float Shortestdist = INT_MAX;
		
		for (int i = 0; i < current->NodeArrayConnections.Num(); i++)
		{
			if(current->NodeArrayConnections[i]->bVisited == false)
			{
				UE_LOG(LogTemp, Warning, TEXT("manyloop"));

				float shortestEdge = current->GetDistanceTo(StarNodeArray[i]);

				if(Shortestdist > shortestEdge)
				{
					current->NodeArrayConnections[i]->PrevStarNode = current;
					// DrawDebugLine(GetWorld(), current->NodeLocation,
					// 				current->NodeArrayConnections[i]->NodeLocation, FColor::Green,
					// 				false, (0.5* i+1), 0, 10);
				
					StarNodeMap.Emplace(shortestEdge, current->NodeArrayConnections[i]);
				}
				// current->NodeArrayConnections[i]->PrevStarNode = current;
				// // DrawDebugLine(GetWorld(), current->NodeLocation,
				// // 				current->NodeArrayConnections[i]->NodeLocation, FColor::Green,
				// // 				false, (0.5* i+1), 0, 10);
				//
				// StarNodeMap.Emplace(shortestEdge, current->NodeArrayConnections[i]);
			}
		}
		current->bVisited = true;
		StarNodeMap.KeySort([](float A, float B){return A<B;});
		Cheapest = StarNodeMap.begin().Value();
		
		if(current->PrevStarNode != nullptr)
			DrawDebugLine(GetWorld(), current->NodeLocation,
								current->PrevStarNode->NodeLocation, FColor::Purple,
								false, (20), 0, 10);
		current = Cheapest;
		UE_LOG(LogTemp, Warning, TEXT("sortkey"));

		StarNodeMap.Remove(StarNodeMap.begin().Key());
		
		int ctr = 0;
		for (int i = 0; i < StarNodeArray.Num(); i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("check if all visited"));

			if(StarNodeArray[i]->bVisited ==true)
			{
				ctr++;
			}
			if(ctr == StarNodeMap.Num())
			{
				ikkjeBesokt = true;
			}
		}
		

		
		getUsOut++;
	}

	if(current != nullptr && Source != nullptr)
		DrawDebugLine(GetWorld(), current->NodeLocation,
							Source->NodeLocation, FColor::Red,
							false, (20), 0, 10);


	
    // 1 Initialize all vertices as unvisited.
    // 2 Select an arbitrary vertex, set it as the current vertex u. Mark u as visited.
    // 3 Find out the shortest edge connecting the current vertex u and an unvisited vertex v.
    // 4 Set v as the current vertex u. Mark v as visited.
    // 5 If all the vertices in the domain are visited, then terminate. Else, go to step 3.

	
}


void AAStarGraph::AStarSearch()
{
	//init

	for (int i = 0; i < StarNodeArray.Num(); i++)
	{
		StarNodeArray[i]->DistFromStart = INT_MAX;
		StarNodeArray[i]->bVisited = false;
	}


	int rngStart = FMath::RandRange(0,4);
	int rngEnd = FMath::RandRange(17,20);
	
	AAStarNode* StartNode = StarNodeArray[rngStart];
	AAStarNode* EndNode = StarNodeArray[rngEnd];

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

				float heuristic = current->NodeArrayConnections[i]->GetDistanceTo(EndNode);

				float totalcost = distance + current->DistFromStart + heuristic;

				if(totalcost < current->NodeArrayConnections[i]->DistFromStart)
				{
					current->NodeArrayConnections[i]->DistFromStart = totalcost;
					current->NodeArrayConnections[i]->PrevStarNode = current;	
				}

				StarNodeMap.Emplace(current->NodeArrayConnections[i]->DistFromStart, current->NodeArrayConnections[i]);

				DrawDebugLine(GetWorld(), current->NodeLocation,
				current->NodeArrayConnections[i]->NodeLocation, FColor::Green,
				false, (0.5* i+1), 0, 10);
			
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
		
		UE_LOG(LogTemp, Warning, TEXT("The ctrEX value is: %d"), ctrEX);
		UE_LOG(LogTemp, Warning, TEXT("The EndNode->bVisited value is %s"), ( EndNode->bVisited ? TEXT("true") : TEXT("false") ));

		ctrEX++;
	}
	

	
}


void AAStarGraph::DijkstraBoys() // class AAStarNode* start, class AAStarNode* end
{

	//init

	for (int i = 0; i < StarNodeArray.Num(); i++)
	{
		StarNodeArray[i]->DistFromStart = INT_MAX;
		StarNodeArray[i]->bVisited = false;
	}

	int rngStart = FMath::RandRange(0,4);
	int rngEnd = FMath::RandRange(17,20);
	
	
	AAStarNode* StartNode = StarNodeArray[rngStart];
	AAStarNode* EndNode = StarNodeArray[rngEnd];

	
	while (StartNode->NodeArrayConnections.IsEmpty())
	{
		rngStart = FMath::RandRange(0,4);
		StartNode = StarNodeArray[rngStart];
	
	}
	while (StartNode->NodeArrayConnections.IsEmpty())
	{
		rngEnd = FMath::RandRange(17,20);
		EndNode = StarNodeArray[rngEnd];
		
	}
	
	

	// AAStarNode* StartNode = StarNodeArray[0];
	// AAStarNode* EndNode = StarNodeArray[28];

	if(!StartNode)
		return;
	if(!EndNode)
		return;

	StartNode->DistFromStart = 0.f;

	int ctrEX = 0;

	AAStarNode* current = StartNode;
	if(!current)
		return;

	//faulty check if its no road from beginning

	if(current->NodeArrayConnections.IsEmpty())
	{
		UE_LOG(LogTemp,Warning, TEXT("current has no connections, try again!"));
		return;
	}
	
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
				false, (0.5* i+1), 0, 10);
			
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
		
		UE_LOG(LogTemp, Warning, TEXT("The ctrEX value is: %d"), ctrEX);
		UE_LOG(LogTemp, Warning, TEXT("The EndNode->bVisited value is %s"), ( EndNode->bVisited ? TEXT("true") : TEXT("false") ));

		ctrEX++;
	}
	

}


void AAStarGraph::randomSpawner()
{

	// should be user input, but for now hardcoded, this is the amount of spheres spawned
	int SpawnCounter = 30;
	// expand array by ten spaces
		
	// the spawner
	UWorld* World = GetWorld();
	if (World)
	{
		for (int i = 0; i < SpawnCounter; i++)
		{

			double MaxRange = 1500.f;
			double RangeX = FMath::RandRange(-MaxRange, MaxRange);
			double RangeY = FMath::RandRange(-MaxRange, MaxRange);
			double RangeZ = FMath::RandRange(-MaxRange, MaxRange);
			FVector Location =  FVector(RangeX, RangeY, RangeZ);
			
			AAStarNode* StarNode = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, Location, FRotator::ZeroRotator);
			// adds spawned instances to array, if they are the first, they are made source, and the last is made into the target -- ideally this should be by userinput as well (clicking on screen)
			if (StarNode)
			{
				StarNodeArray.Add(StarNode);
			}		
		}
	}	
	



	
}

void AAStarGraph::setDynamicEdges()
{

	float pi = PI;
	

	for (int i = 0; i < StarNodeArray.Num(); i++)
	{

		float random = FMath::RandRange(800.f, 1300.f);

		
		for (int j = 0; j < StarNodeArray.Num()-1; j++)
		{
			if(i==j){continue;}
			if(StarNodeArray[i]->GetDistanceTo(StarNodeArray[j]) <= random)
			{
				StarNodeArray[i]->NodeArrayConnections.Add(StarNodeArray[j]);
			}
		}
		
	}

	

	for (int i = 0; i < StarNodeArray.Num(); i++)
	{
		while (StarNodeArray[i]->NodeArrayConnections.IsEmpty())
		{

			for (int j = 0; j < StarNodeArray.Num()-1; j++)
			{
				if(i==j){continue;}
				float random = FMath::RandRange(1000.f, 2500.f);
				StarNodeArray[i]->NodeArrayConnections.Add(StarNodeArray[j]);
			}
			
					UE_LOG(LogTemp, Warning, TEXT("One mofo is empty"));

		}
	}


}



void AAStarGraph::Run_AStar()
{
	UE_LOG(LogTemp, Warning, TEXT("void AAStarGraph::Run_AStar()"));
	randomSpawner();
	setDynamicEdges();
	AStarSearch();
}
void AAStarGraph::Run_TSP()
{
	UE_LOG(LogTemp, Warning, TEXT("void AAStarGraph::Run_TSP()"));
	randomSpawner();
	setDynamicEdges();
	LonesomeTraveler();
}
void AAStarGraph::Run_Dijkstra()
{
	UE_LOG(LogTemp, Warning, TEXT("void AAStarGraph::Run_Dijkstra()"));
	randomSpawner();
	setDynamicEdges();
	DijkstraBoys();
}