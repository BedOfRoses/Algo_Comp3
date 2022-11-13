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

	/*bool to keep track of if have visited node*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct Vertex")
	bool b_HasVisitedNode = false;

	/* locations of nodes */
	/* location of this node */
	UPROPERTY(VisibleAnywhere, Category = "StarNode Vector")
	FVector HomeVertexVector;
	/* location of foreign node1 */
	UPROPERTY(VisibleAnywhere, Category = "StarNode Vector")
	FVector ForeignVertexVector_one;
	/* location of foreign node2 */
	UPROPERTY(VisibleAnywhere, Category = "StarNode Vector")
	FVector ForeignVertexVector_two;
	/* location of foreign node3 */
	UPROPERTY(VisibleAnywhere, Category = "StarNode Vector")
	FVector ForeignVertexVector_three;
	/* location of foreign node4 */
	UPROPERTY(VisibleAnywhere, Category = "StarNode Vector")
	FVector ForeignVertexVector_four;

public:
	/*constructor/destructor*/
	FStarNodeStruct();
	~FStarNodeStruct();
};
