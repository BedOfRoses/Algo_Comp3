// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarGraph.h"
#include "AStarNode.h"

// Sets default values
AAStarGraph::AAStarGraph()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAStarGraph::BeginPlay()
{
	Super::BeginPlay();

	NodesArray.Init(AStarNode, 8);
	
}

// Called every frame
void AAStarGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

