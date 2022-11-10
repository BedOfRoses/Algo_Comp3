// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarGraph.h"
#include "AStarNode.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "DrawDebugHelpers.h"

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

	
}

// Called every frame
void AAStarGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//BoxScan();
	SetUpEdges();

	// TestConnection(startNodeBoy, endNodeBoy);
	
}


void AAStarGraph::SpawnSetAmountOfNodes()
{
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



	
	
	
	
}


void AAStarGraph::SetUpEdges()
{

	for (int i = 0; i < StarNodeArray.Num()-1; i++)
	{
		DrawDebugLine(GetWorld(),StarNodeArray[i]->NodeLocation, StarNodeArray[i+1]->NodeLocation, FColor::Emerald, false, -1, 0, 5);

		// DrawDebugLine(GetWorld(),start->NodeLocation, end->NodeLocation,FColor::Emerald,false,-1,0,5);
	
	}

	
}


void AAStarGraph::TestConnection(class AAStarNode* start, class AAStarNode* end)
{

	start = startNodeBoy;
	end = endNodeBoy;

	DrawDebugLine(GetWorld(),start->NodeLocation, end->NodeLocation,FColor::Emerald,false,-1,0,5);
	
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
