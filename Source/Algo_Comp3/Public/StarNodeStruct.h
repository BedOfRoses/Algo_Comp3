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

public:
	/*constructor/destructor*/
	FStarNodeStruct();
	~FStarNodeStruct();
};
