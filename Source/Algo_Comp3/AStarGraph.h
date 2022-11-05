// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nodes")
	TArray<class AAStarNode*> StarNodeArray;

	// Used to call the blueprint class!
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AAStarNode> starnodeBP;

	int AmountOfNodesToCreate;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Was supposed to scale up and overlap with the other starnodes. However, not in use for the moment!
	void BoxScan();
	void SpawnStarNodes();


	/* Algorithms */
public:

	void AStarSearch();
	void Dijkstra(class AAStarGraph* graph, class AAStarNode* source);

	int SetAmountOfNodesToCreate(int AON) { return AmountOfNodesToCreate = AON; }
	float minDistance(float dist[], bool sptSet[]);

};





////////////////////////////////// Garbage


// Used to find the other nodes when scanning
	/*UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult);*/

			//TArray<class AStarNode> NodesArray;

				//TSubclassOf<AActor> starnodeClass;

				//class AAStarNode* AStarNode;


				//std::list<AAStarNode*> starnodes;