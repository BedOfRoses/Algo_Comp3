// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AStarNode.h"
#include "GameFramework/Actor.h"
#include "AStarGraph.generated.h"


UCLASS()
class ALGO_COMP3_API AAStarGraph : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAStarGraph();

	/*Sole purpose to increase a certain size and then stop*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoxComp")
	class UBoxComponent* BoxComponent;

	/* Array of all nodes in scene*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nodes")
	TArray<class AAStarNode*> StarNodeArray;
	

	// Used to call the blueprint class!
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AAStarNode> starnodeBP;

	// If the user wants to add a certain amount of nodes to scene. (WIP**)
	int AmountOfNodesToCreate{};

	/* Used to get the cheapest path during the TMap popping/clearing */
	UPROPERTY()
	AAStarNode* Cheapest = nullptr;

	UPROPERTY()
	AAStarNode* Next = nullptr;

	/* Used to sort and select path*/
	UPROPERTY(EditAnywhere, Category = "StarNodeMap")
	TMap<float, AAStarNode*> StarNodeMap; 


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	


	/*Paperboys*/
	void LonesomeTraveler();
	void AStarSearch();
	void DijkstraBoys();
	

	// for nodes functions
	void randomSpawner(); // dynamic
	void setDynamicEdges();
	
	void SpawnSetAmountOfNodes();
	void DrawEdges();
	void CreateEdges();

	int SetAmountOfNodesToCreate(int AON) { return AmountOfNodesToCreate = AON; } // not used yet.



	void Run_AStar();
	void Run_TSP();
	void Run_Dijkstra();

	
};


