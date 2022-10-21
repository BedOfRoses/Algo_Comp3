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


	TArray<class AStarNode> NodesArray;

	TSubclassOf<AActor> starnodeClass;

	class AAStarNode* AStarNode;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
