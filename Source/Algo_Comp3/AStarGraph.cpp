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

	//SpawnStarNodes();

	//BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AAStarGraph::OnOverlap);

	//BoxComponent->OnComponentBeginOverlap.__Internal_AddDynamic(this, &AAStarGraph::OnOverlap);

	//BoxScan();

	//NodesArray.Init(AStarNode, 8);

	// Test spawning
	// if(starnodeBP)
	// {
	// 	startNodeBoy = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, FVector(100.f,101.f,100.f), FRotator::ZeroRotator);
	//
	// 	endNodeBoy = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, FVector(50.f,500.f,100.f), FRotator::ZeroRotator);
	// 	
	// }
	//
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
	

	/*
	// Set up connections
	// "Top left" 0
	StarNodeArray[0]->connection1 = StarNodeArray[1];
	StarNodeArray[0]->connection2 = StarNodeArray[3];
	StarNodeArray[0]->connection3 = StarNodeArray[4];


	// top middle 1
	//StarNodeArray[1]->connection1 = StarNodeArray[0]; // connecting back
	StarNodeArray[1]->connection1 = StarNodeArray[2];
	StarNodeArray[1]->connection2 = StarNodeArray[2];
	StarNodeArray[1]->connection3 = StarNodeArray[4];
	StarNodeArray[1]->connection4 = StarNodeArray[5];

	// "top right" 2
	StarNodeArray[2]->connection1 = StarNodeArray[1]; // this one is already connected in "top middle" loop
	StarNodeArray[2]->connection2 = StarNodeArray[4];
	StarNodeArray[2]->connection3 = StarNodeArray[5];
	
	// "middle left" 3
	StarNodeArray[3]->connection1 = StarNodeArray[0]; // this one is already connected in top left
	StarNodeArray[3]->connection2 = StarNodeArray[1];
	StarNodeArray[3]->connection3 = StarNodeArray[4];
	StarNodeArray[3]->connection4 = StarNodeArray[6];
	StarNodeArray[3]->connection5 = StarNodeArray[7];


	// "middle middle" 4
	StarNodeArray[4]->connection1 = StarNodeArray[0];
	StarNodeArray[4]->connection2 = StarNodeArray[1];
	StarNodeArray[4]->connection3 = StarNodeArray[2];
	StarNodeArray[4]->connection4 = StarNodeArray[3];
	StarNodeArray[4]->connection5 = StarNodeArray[5];
	StarNodeArray[4]->connection6 = StarNodeArray[6];
	StarNodeArray[4]->connection7 = StarNodeArray[7];
	StarNodeArray[4]->connection8 = StarNodeArray[8];

	// "middle right" 5
	StarNodeArray[5]->connection1 = StarNodeArray[1];
	StarNodeArray[5]->connection2 = StarNodeArray[2];
	StarNodeArray[5]->connection3 = StarNodeArray[4];
	StarNodeArray[5]->connection4 = StarNodeArray[7];
	StarNodeArray[5]->connection5 = StarNodeArray[8];

	// "bottom left" 6
	StarNodeArray[6]->connection1 = StarNodeArray[3];
	StarNodeArray[6]->connection2 = StarNodeArray[4];
	StarNodeArray[6]->connection3 = StarNodeArray[7];
	

	// "bottom middle" 7
	StarNodeArray[7]->connection1 = StarNodeArray[3];
	StarNodeArray[7]->connection2 = StarNodeArray[4];
	StarNodeArray[7]->connection3 = StarNodeArray[5];
	StarNodeArray[7]->connection4 = StarNodeArray[6];
	StarNodeArray[7]->connection5 = StarNodeArray[8];
	
	// "bottom right" 8
	StarNodeArray[8]->connection1 = StarNodeArray[4];
	StarNodeArray[8]->connection2 = StarNodeArray[5];
	StarNodeArray[8]->connection2 = StarNodeArray[7];

*/
	
	
	
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

	for (int i = 0; i < StarNodeArray.Num(); i++)
	{
		for (int j = 0; j < StarNodeArray[i]->NodeArrayConnections.Num(); j++)
		{

			/* Setting the cost for the nodes	*/
			StarNodeArray[i]->NodeArrayConnections[j]->Cost = StarNodeArray[i]->GetDistanceTo(StarNodeArray[i]->NodeArrayConnections[j]);


			
			// DirectionPerConnection.Add(StarNodeArray[i]->NodeArrayConnections[j]->NodeLocation - StarNodeArray[i]->NodeLocation);
			// StarNodeArray[i]->NodeArrayConnections[j]->Cost = UKismetMathLibrary::Distance2D(StarNodeArray[i]->NodeArrayConnections[j]->NodeLocation - StarNodeArray[i]->NodeLocation);
			// UE_LOG(LogTemp,Warning,	TEXT("Dir %s"), *DirectionPerConnection[i].ToString());
			
	
		}
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
			

		/*	THIS WORKS!!!!1	*/
		 // if(StarNodeArray[i]->connection1 != nullptr)
		 // 	DrawDebugLine(GetWorld(),StarNodeArray[i]->NodeLocation, StarNodeArray[i]->connection1->NodeLocation, FColor::Emerald, false, -1, 0, 5);
		 // 	
		 // if(StarNodeArray[i]->connection2 != nullptr)
		 // 	DrawDebugLine(GetWorld(),StarNodeArray[i]->NodeLocation, StarNodeArray[i]->connection2->NodeLocation, FColor::Red, false, -1, 0, 5);
		 // 	
		 // if(StarNodeArray[i]->connection3 != nullptr)
		 // 	DrawDebugLine(GetWorld(),StarNodeArray[i]->NodeLocation, StarNodeArray[i]->connection3->NodeLocation, FColor::Blue, false, -1, 0, 5);
		 // 	
		 // if(StarNodeArray[i]->connection4 != nullptr)
		 // 	DrawDebugLine(GetWorld(),StarNodeArray[i]->NodeLocation, StarNodeArray[i]->connection4->NodeLocation, FColor::Blue, false, -1, 0, 5);
		 // 	
		 // if(StarNodeArray[i]->connection5 != nullptr)
		 // 	DrawDebugLine(GetWorld(),StarNodeArray[i]->NodeLocation, StarNodeArray[i]->connection5->NodeLocation, FColor::Red, false, -1, 0, 5);
		 // 	
		 // if(StarNodeArray[i]->connection6 != nullptr)
		 // 	DrawDebugLine(GetWorld(),StarNodeArray[i]->NodeLocation, StarNodeArray[i]->connection6->NodeLocation, FColor::Red, false, -1, 0, 5);
		 // 	
		 // if(StarNodeArray[i]->connection7 != nullptr)
		 // 	DrawDebugLine(GetWorld(),StarNodeArray[i]->NodeLocation, StarNodeArray[i]->connection7->NodeLocation, FColor::Purple, false, -1, 0, 5);
		 // 	
		 // if(StarNodeArray[i]->connection8 != nullptr)
		 // 	DrawDebugLine(GetWorld(),StarNodeArray[i]->NodeLocation, StarNodeArray[i]->connection8->NodeLocation, FColor::Emerald, false, -1, 0, 5);

		// if(StarNodeArray[i]->connection1 != nullptr &&
		// 	StarNodeArray[i]->connection2 != nullptr &&
		// 	StarNodeArray[i]->connection3 != nullptr &&
		// 	StarNodeArray[i]->connection4 != nullptr &&
		// 	StarNodeArray[i]->connection5 != nullptr &&
		// 	StarNodeArray[i]->connection6 != nullptr &&
		// 	StarNodeArray[i]->connection7 != nullptr &&
		// 	StarNodeArray[i]->connection8 != nullptr )
		// {
		//
		// 	DrawDebugLine(GetWorld(),StarNodeArray[i]->NodeLocation, StarNodeArray[i+1]->NodeLocation, FColor::Emerald, false, -1, 0, 5);
		// 	
		// }

	}


	
		// for (int j = 0; j < StarNodeArray[i]->connections.Num();j++)
		// {
		// 	DrawDebugLine(GetWorld(),StarNodeArray[i]->NodeLocation, StarNodeArray[i]->connections[j]->NodeLocation, FColor::Emerald, false, -1, 0, 5);
		// }
		// DrawDebugLine(GetWorld(), StarNodeArray[i]->connections[i]->NodeLocation, StarNodeArray[i+1]->connections[i]->NodeLocation, FColor::Purple,false,-1,0,5);
		// DrawDebugLine(GetWorld(),start->NodeLocation, end->NodeLocation,FColor::Emerald,false,-1,0,5);
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

void AAStarGraph::BoxScan()
{
	
	//FVector BoxSize = GetActorBounds();
	FVector ActorScale = GetActorScale();

	bool isBoxBigEnough = false;

	if (isBoxBigEnough == false) 
	{
		for (float i = 0.f; i < 10.f; i++)
		{
			SetActorScale3D(FVector(i, i, i));
		}
		isBoxBigEnough = true;
	}
	


}





//void AAStarGraph::OnOverlap(
//	UPrimitiveComponent* OverlappedComponent,
//	AActor* OtherActor, 
//	UPrimitiveComponent* OtherComponent,
//	int32 OtherbodyIndex, 
//	bool bFromSweep, 
//	const FHitResult& SweepResult
//)
//{
//
//	if(OtherActor->IsA(AAStarNode::StaticClass()))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Hit AStarNode"))
//
//		/*if (GEngine) {
//			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("DebugTest"));
//		}*/
//	
//	}
//
//	//UE_LOG(LogTemp, Warning, TEXT("Hit AStarNode"))
//
//
//
//}



////GetWorld()->SpawnActor(FVector(1.f,1.f,1.f),FRotator(1.f,1.f,1.f),FactoryTransactionAnnotation);
//
//		//GetWorld()->SpawnActor(AAStarNode* StarNode, FName::ToString("Starnode"), )
//
//if (starnodeBP == nullptr)
//return;
//
//
////UWorld::SpawnActor(starnodeBP, FVector(i * 0.f, i * 0.f, i * 0.f), FRotator(0.f));
//
///*UWorld* world;
//if (world) {
//
//	FActorSpawnParameters spawnParams;
//	spawnParams.Owner = this;
//
//	FRotator rotator;
//	FVector SpawnLocation = FVector(i * 0.f, i * 0.f, i * 0.f);
//
//	world->SpawnActor<AAStarNode>(starnodeBP, SpawnLocation, rotator, spawnParams);
//
//
//}*/
//
//
///*AAStarNode* StarNode = GetWorld()->SpawnActor<AAStarNode>(AAStarNode::StaticClass(),
//	FVector(i * 0.f, i * 0.f, i * 0.f),
//	FRotator(0.f, 0.f, 0.f));*/
//
//
//
//	}



// AAStarNode* newStar1 = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, FVector(1000.f,  1000.f, 10.f),FRotator::ZeroRotator);
// AAStarNode* newStar2 = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, FVector(2000.f,  1000.f, 10.f),FRotator::ZeroRotator);
// AAStarNode* newStar3 = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, FVector(3000.f,  1000.f, 10.f),FRotator::ZeroRotator);
// AAStarNode* newStar4 = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, FVector(1000.f,  2000.f, 10.f),FRotator::ZeroRotator);
// AAStarNode* newStar5 = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, FVector(2000.f,  2000.f, 10.f),FRotator::ZeroRotator);
// AAStarNode* newStar6 = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, FVector(3000.f,  2000.f, 10.f),FRotator::ZeroRotator);
// AAStarNode* newStar7 = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, FVector(1000.f,  3000.f, 10.f),FRotator::ZeroRotator);
// AAStarNode* newStar8 = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, FVector(2000.f,  3000.f, 10.f),FRotator::ZeroRotator);
// AAStarNode* newStar9 = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, FVector(3000.f,  3000.f, 10.f),FRotator::ZeroRotator);


/*  // Trying to loop sheesh
	int axis = 1;
	int axis2 = 1;
	// Spawning loop for new nodes.
	for (int i = 0; i < 9; i++)
		{
			axis2 = i;
			if(i % 3 == 0){ axis +=1; axis2 +=1;}
			AAStarNode* newStar = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, FVector((axis * 100.f), (axis2 * 100.f), 10.f),FRotator::ZeroRotator);
			newStar->nodeID = i;
			newStar->bTimeToGoCrazy = false;
		}
		*/
