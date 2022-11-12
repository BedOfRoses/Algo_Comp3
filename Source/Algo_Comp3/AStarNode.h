// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
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

	/* S */
	


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
