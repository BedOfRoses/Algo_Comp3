// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarGraph.h"
#include "AStarNode.h"
#include "StarNodeStruct.h"
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

	// SpawnSetAmountOfNodes(); --> Simon's it was active, but for testing purposes I've turned it off

	SpawnerTestingFacility();
	
}

// Called every frame
void AAStarGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//BoxScan();

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
			
			
			AAStarNode* newStar = GetWorld()->SpawnActor<AAStarNode>(starnodeBP, FVector(xAxis * 1000.f,  yAxis * 1000.f, 10.f),FRotator::ZeroRotator);
			newStar->nodeID = i;
			
		}



		
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

/* ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------- */
void AAStarGraph::SpawnerTestingFacility() // sara - spawner (DONE)
{
	// should be user input, but for now hardcoded, this is the amount of spheres spawned
	int SpawnCounter = 10;
	// expand array by ten spaces
		
	// the spawner
	UWorld* World = GetWorld();
	if (World)
	{
		FRotator Rotation = FRotator(0, 0, 0);
		for (int i = 0; i < SpawnCounter; i++)
		{
			// make a random location
			FVector Location = GetRandomLocation();
			// make object
			AAStarNode* VertexSpawned = GetWorld()->SpawnActor<AAStarNode>(BP_VertexSpawn, Location, Rotation);
			// adds spawned instances to array, if they are the first, they are made source, and the last is made into the target -- ideally this should be by userinput as well (clicking on screen)
			if (VertexSpawned)
			{
				BP_VertexSpawnArray.Add(VertexSpawned); 

				if (i == 0 && !VertexSpawned->ForThisSphere.b_IsThisNodeSource)
				{
					VertexSpawned->ForThisSphere.b_IsThisNodeSource = true;
				}
				else if (i == SpawnCounter && !VertexSpawned->ForThisSphere.b_IsThisNodeTarget)
				{
					VertexSpawned->ForThisSphere.b_IsThisNodeTarget = true;
				}
			}
			
		}
	}
	
	//everything is spawned and ready to have paths applied to them
	GiveVertecisPaths(); // ------ this is problematic, somehow :(, and now it isn't. wth
}

FVector AAStarGraph::GetRandomLocation() // sara - get random location for spawn (DONE)
{
	double MaxRange = 1000.f;

	double RangeX = FMath::RandRange(-MaxRange, MaxRange);
	double RangeY = FMath::RandRange(-MaxRange, MaxRange);
	double RangeZ = FMath::RandRange(-MaxRange, MaxRange);
		
	return FVector(RangeX, RangeY, RangeZ);
}

void AAStarGraph::GiveVertecisPaths() // sara - makes connections between starnodes according to their spawn location (DONE)
{
	// find distance between nodes and check if they should be connected
	for (int i = 0; i < BP_VertexSpawnArray.Num(); i++)
	{
		// is current node Target
		if (BP_VertexSpawnArray[i]->ForThisSphere.b_IsThisNodeTarget == true)
		{
			// return;
		}
		else
		{
			// to compare distances between nodes
			float Distance;
			for (int u = 0; u < BP_VertexSpawnArray.Num(); u++)
			{
				// if the current node is not the same as the node we are currently looping through
				if (BP_VertexSpawnArray[i] != BP_VertexSpawnArray[u])
				{
					if (BP_VertexSpawnArray[i]->arr_connections.Num() == 4)
					{

					}
					else
					{
						Distance = FVector::Dist(BP_VertexSpawnArray[i]->ForThisSphere.ThisNodeLocation, BP_VertexSpawnArray[u]->ForThisSphere.ThisNodeLocation);
						// if this is the first node calculated, insert anyway
						if (BP_VertexSpawnArray[i]->arr_connections.Num()==0)
						{
							BP_VertexSpawnArray[i]->arr_connections.Add(BP_VertexSpawnArray[u]);
							BP_VertexSpawnArray[i]->arr_distances.Add(Distance);
							//arr_DistancesBetweenNodes.Add(Distance);
						}
						// otherwise
						else
						{
							int32 counter = 4;
							for (int k = 0; k < counter; k++)
							{
								if (BP_VertexSpawnArray[i]->arr_distances.IsValidIndex(k))
								{
									if (BP_VertexSpawnArray[i]->ForThisSphere.b_IsThisNodeTarget)
									{
										// do nothing
										// return;
									}
									else if (Distance < BP_VertexSpawnArray[i]->arr_distances[k])
									{
										BP_VertexSpawnArray[i]->arr_distances.Insert(Distance, k);
										//arr_DistancesBetweenNodes.SetNum(4);
										BP_VertexSpawnArray[i]->arr_connections.Insert(BP_VertexSpawnArray[u], k);
										//BP_VertexSpawnArray[i]->arr_connections.SetNum(4);
									}
								}
							}
						}
					}
				}
			}			
		}
	}
	
	int32 count = 749;
	FString MessageToScreen = FString::SanitizeFloat(count);
	if (GEngine) {

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *MessageToScreen);
	}

	FacilitysDrawDebugLine();

	/*for (int i = 0; i < BP_VertexSpawnArray.Num(); i++)
	{
		//basecase
		if (BP_VertexSpawnArray[i]->ForThisSphere.b_IsThisNodeTarget == true)
		{
			return;
		}
		else
		{
			// try to insert element in arr_connections
			// if arr[] is source?
			if (BP_VertexSpawnArray[i]->ForThisSphere.b_IsThisNodeSource == true)
			{
				// yes  - insert
				BP_VertexSpawnArray[i]->arr_connections[0] = BP_VertexSpawnArray[i];
				// BP_VertexSpawnArray[i]->ForThisSphere.ForeignVertecVectorArray[0];
			}
			else
			{
				// no - is arr full? the array is full when it has four insertions
				if (BP_VertexSpawnArray[i]->arr_connections.Num() == 4)
				{
					// yes - check through elements, smaller comes first, greater after - insert, if greater than last element, disregard
					for (int u = 0; u < BP_VertexSpawnArray[i]->arr_connections.Num(); u++)
					{
						float DistanceBetweenNodes;
						if (BP_VertexSpawnArray[i] != BP_VertexSpawnArray[u])
						{							
							DistanceBetweenNodes = FVector::Dist(BP_VertexSpawnArray[i]->ForThisSphere.ThisNodeLocation, BP_VertexSpawnArray[u]->ForThisSphere.ThisNodeLocation);
						}
						// check distance bewteen nodes
						if (arr_DistancesBetweenNodes.Num() == 0)
						{

						}
					}
				}
				else
				{
					// no  - check through elements, smaller comes first, greater after - insert
				}										
			}				
		}
	}
	// node by node is checked in a recursive function, if they aren't the target, they should have a path to 1-4 of 
	// the 4 closest nodes. the connections should be sent to the arr_connection array in each individual node. 
	// after the node is checked, the next node is checked. 
	// when all nodes have their connections, they can be sent to FacilitysDrawDebugLine
	//

	/// how large is array?
	int32 counter = BP_VertexSpawnArray.Num();
	// pick one element from array at a time
	for (int BP_element = 0; BP_element < counter; BP_element++) //here BP_element refer to the instances of initialised StarNodes in stored in the BP_VertecSpawnArray
	{
		// get elements 'realspace' location
		VertexLocation = BP_VertexSpawnArray[BP_element]->GetActorLocation(); // and this is a problem, now 
		// get distance to all other elements in array
		for (int OtherNode = 0; OtherNode < ForeignVertecisLocations.Num(); OtherNode++) //here the OtherNode refer to the StarNodes that the element from the first for_loop will be pointing towards
		{
			// get actor FVector
			FVector OtherVertecisLocation = BP_VertexSpawnArray[OtherNode]->GetActorLocation();
			if (VertexLocation != OtherVertecisLocation) //if the node is itself, it will pass it. 
			{
				// find distances and put them in array
				VertecisDistances.Emplace(FVector::Dist(VertexLocation, OtherVertecisLocation));
				// put foreign locations in an array
				ForeignVertecisLocations[OtherNode] = OtherVertecisLocation; // this is marked down as problematic | was because used counter instead of actual array size
			}
		}
		// sort array
		// VertecisDistances.Sort(); ------------------------------------------> somehow after two and a half hours, this dosen't work any longer after having tested if it was better to hace the struct inside StarNode or not. WTF
		// then pop them so only the four are left 
		if (VertecisDistances.IsValidIndex(counter-1) && ForeignVertecisLocations.IsValidIndex(counter-1)) //checks if these are full or not
		{
			VertecisDistances.SetNum(4);
			ForeignVertecisLocations.SetNum(4);
		}
		UE_LOG(LogTemp, Warning, TEXT("StarGraph, does log works? :("));
		// let's hope nothing else breaks
		// //here we should try to get the vector and insert into struct!
		// accessing struct here to test if i can reach from star graph
		// ForThisSphere.ForeignVertexVector_one = ForeignNode->
		int32 WhoGetsPaths = FMath::RandRange(0, 4); // this is currently a counter ----------------- I think this needs to be in starGraph. Its the only way this pointer is going to work. omg
		for (int i = 0; i < WhoGetsPaths; i++) //here we will add pointers to the OtherNode's locations in home-node
		{
			//AAStarNode* ForeignNode; // does it want this to be in .h? --> I need a different pointer now omg
			//ForeignNode->ForThisSphere.ForeignVertecVectorArray[i] = ForeignVertecisLocations[i];
			if (ForeignVertecisLocations.IsValidIndex(0)) //checks if foreign vertecisLocation array is valid, that there are values there
			{
				UE_LOG(LogTemp, Warning, TEXT("StarGraph, if ForeignVertecisLocation.IsValidIndex is true or not"));

				ForeignNode = BP_VertexSpawnArray[i];
				ForeignNode->ForThisSphere.ForeignVertecVectorArray[i] = ForeignVertecisLocations[i];
			}
			// add pointer to these elements in struct
			//InsertVectorLocationInHomeNode(VertecisDistances[i]);
			//ForThisSphere.ForeignVertecVectorArray[i] = ForeignNode->ForeignVertecisLocations[i];
		}
		// can i read the information about foreign vertex locations now?
		if(ForeignVertecisLocations.IsValidIndex(0))
		{
			FString ForeignVertecisLocationsDisplayMessage = FString::SanitizeFloat(ForeignNode->ForThisSphere.ForeignVertecVectorArray[0].X); //this makes it crash because it might not be an array yet???
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Purple, *ForeignVertecisLocationsDisplayMessage);
			}
		}
		//IT DIDNT CRASH UE! omg
		
		GiveThemPointers(ForeignNode);
		
		
		//should this be in starnode?? Attempts --- put it in StarNode.cpp
		// random element of 1-4 gets a pointer to them
		//int32 WhoGetsPaths = FMath::RandRange(0, 4); // this is currently a counter
		//for (int i = 0; i < WhoGetsPaths; i++) //here we will add pointers to the OtherNode's locations in home-node
		//{
		//	// add pointer to these elements in struct
		//	//InsertVectorLocationInHomeNode(VertecisDistances[i]);
		//	
		//}
		
	}
	// send to draw debug line to draw these lines
	*/
}

void AAStarGraph::FacilitysDrawDebugLine()	// sara - (DONE) no distances
{
	// for-loop through entire arr_node in a recursive function. BaseCase is if node is target. 
	for (int i = 0; i < BP_VertexSpawnArray.Num(); i++)
	{
		// if they aren't, another for-loop is started looping through the node's arr_connections
		if (BP_VertexSpawnArray[i]->ForThisSphere.b_IsThisNodeTarget == true)
		{
			// return;
		}
		else
		{
			// for every node an instance of path is made and stored in an array in their struct.
			for (int u = 0; u < BP_VertexSpawnArray[i]->arr_connections.Num(); u++)
			{
				// start node
				FVector StartNode = BP_VertexSpawnArray[i]->ForThisSphere.ThisNodeLocation;
				// end node
				FVector EndNode = BP_VertexSpawnArray[i]->arr_connections[u]->ForThisSphere.ThisNodeLocation;
				DrawDebugLine(GetWorld(), StartNode, EndNode, FColor::Red, true, -1.f, 0.f, 10.f);
			}
			// when all the nodes have had their paths drawn, the presentation is done and we are ready to navigate between nodes
		}		
	}
	
	/*// how many elements in array?
	// for every element
	// draw line to what they are pointing at
	// 	for (int i = 0; i < StarNodeArray.Num()-1; i++)

	// yoinked from simon for easy reading
	/*for (int j = 0; j < StarNodeArray[i]->NodeArrayConnections.Num(); j++)
		DrawDebugLine(GetWorld(), StarNodeArray[i]->NodeLocation, StarNodeArray[i]->NodeArrayConnections[j]->NodeLocation, FColor::Emerald, false, -1, 0, 5);*/
	
	// finished
}

/* ------------------------------------------------------------------------------------------------------------------------- */
												     // Djikstra
/* ------------------------------------------------------------------------------------------------------------------------- */
void AAStarGraph::DjikstraAlgorithm()
{
	int pathCounter = 0;

	for (int i = 0; i < BP_VertexSpawnArray.Num(); i++)
	{
		if (BP_VertexSpawnArray[i]->ForThisSphere.b_IsThisNodeSource)
		{
			DjikstraPath[pathCounter] = BP_VertexSpawnArray[i];
			pathCounter++;
		}
		if (!BP_VertexSpawnArray[i]->ForThisSphere.b_IsThisNodeTarget)
		{
			for (int u = 0; u < BP_VertexSpawnArray[i]->arr_connections.Num(); u++)
			{
				if (BP_VertexSpawnArray[i]->arr_connections[u]->ForThisSphere.b_HasVisitedNode)
				{
					//pass
				}
				else if (!BP_VertexSpawnArray[i]->arr_connections[u]->ForThisSphere.b_HasVisitedNode)
				{
					DjikstraPath.Add(BP_VertexSpawnArray[i]->arr_connections[u]);
					pathCounter++;
					break;
				}
			}
		}
		else if (BP_VertexSpawnArray[i]->ForThisSphere.b_IsThisNodeTarget)
		{
			DjikstraPath[pathCounter] = BP_VertexSpawnArray[i];
		}
	}
/*
 function Djikstra
	this node
		who connected with
		if not visited
			compare distance
			chose shortest
			put distance in path arr
			move to that node
		if all nodes are visited
			error
*/
}
/* ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------- */

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
	//int min = INT_MAX, min_index; //somhow, this is now a problem, I haven't even touched this one! It's been half a week!
	float min_index = 1; //I just want it not to bother me, commented everything out except the new line to initialise min index
	/*for (int v = 0; v < AmountOfNodesToCreate; v++)
	{

		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	}*/
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
