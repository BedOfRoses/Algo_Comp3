// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "StarNodeStruct.h"
// #include "AStarGraph.h" //this might be a problem later on. I was right, circular dependencies bby!
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AStarNode.generated.h"


//USTRUCT(BlueprintType)
//struct FVertexNodePackage {
//
//	GENERATED_BODY()
//
//	/*Vertex ID*/
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct Vertex")
//	int32 VertexID;
//
//	/*Vertex datapackage*/
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct Vertex")
//	int32 DataPackage;
//
//	/*bool to keep track of if have visited node*/
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct Vertex")
//	bool b_HasVisitedNode = false;
//
//};

UCLASS()
class ALGO_COMP3_API AAStarNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAStarNode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeMesh")
	class UStaticMeshComponent* NodeMesh;

	/*
	We need 3 materials, one for start, one for end and one for the others :)
		- Green = start
		- red = end
		- white = lmao


	Position (x,y,z) for this specific node.

	*/
	
	/* to identify which node is which. --> also have one in Struct*/
	int32 nodeID; 

	/* Store which other nodes point to THIS node */
	TArray<AAStarNode*> connections;
	//location of this node
	FVector NodeLocation;

	float timeCheckToGoCrazy = 10.f; // checker if >
	float timerToGoCrazy; // increases
	
	bool bTimeToGoCrazy = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*functions*/
	void GoCrazy();
	void LineTraceTest();
	void LineTraceMyOwn();



	/* Testing facility StarNodeVersion */
	// pointers ~ <3 
	AAStarNode* ToGetOtherNodes = NULL;
	void AssignIndividualVertexStructs();
	//individual Structs initialised for each instance of it
	FStarNodeStruct ForThisSphere; 
	
	/* foreign nodes that this node has paths to */
	TArray<AAStarNode*>arr_connections;

	/* distances between the chosen nodes */
	TArray<float>arr_distances;

	/* paths to the nodes this node has connections to*/
	//TArray<APaths*>arr_paths;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Vertex | Material")
	UMaterial* Material;

	void SetMat();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Vertex | Material")
		UMaterial* VisitedMaterial;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Vertex | Material")
		UMaterial* NotVisitedMaterial;
};




////// garbage

/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* NodeTwoMesh;*/

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeSphere")
	//class USphereComponent* NodeSphere;


//virtual void DrawDebugLine
	//(
	//	const UWorld* InWorld,
	//	FVector const& LineStart,
	//	FVector const& LineEnd,
	//	FColor const& Color,
	//	bool bPersistentLines,
	//	float LifeTime,
	//	uint8 DepthPriority,
	//	float Thickness
	//);


	//AAStarNode* connections[];
