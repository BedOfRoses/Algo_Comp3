// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StarNodeStruct.generated.h"

/**
 * USTRUCT for StarNode
 */

USTRUCT(BlueprintType)
struct ALGO_COMP3_API FStarNodeStruct
{
	GENERATED_BODY()

public:

	/*Vertex ID*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct Vertex")
	int32 VertexID=10;

	/*Vertex datapackage*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct Vertex")
	int32 DataPackage;

	//location of this node, stored in Struct
	FVector ThisNodeLocation;

	//heuristic value for use with algorithm - measures the value of a direct line between this node and target node
	float HeuristicValue;

	/*bool to keep track of if have visited node*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct Vertex")
	bool b_HasVisitedNode = false;
	/*bool to decide if node is source or not*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct Vertex")
	bool b_IsThisNodeSource = false;
	/*bool to decide if node is target or not*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct Vertex")
	bool b_IsThisNodeTarget = false;

	/* locations of nodes */
	/* location of this node */
	UPROPERTY(VisibleAnywhere, Category = "StarNode Vector")
	FVector HomeVertexVector;
	/* foreign node location array */
	TArray<FVector> ForeignVertecVectorArray;
	
	/* distance to source */
	float DistanceToSource;

	
public:
	/*constructor/destructor*/
	FStarNodeStruct();
	~FStarNodeStruct();
};
