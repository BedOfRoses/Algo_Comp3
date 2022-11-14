// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AStarNode.generated.h"





UCLASS()
class ALGO_COMP3_API AAStarNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAStarNode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeMesh")
	class UStaticMeshComponent* NodeMesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeMaterial")
	class UMaterial* NodeMaterialGreen = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeMaterial")
	class UMaterial* NodeMaterialBlue = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeMaterial")
	class UMaterial* NodeMaterialOrange = nullptr;
	
	/*
	We need 3 materials, one for start, one for end and one for the others :)
		- Green = start
		- red = end
		- white = lmao


	Position (x,y,z) for this specific node.

	*/
	
	/* to indentify which node is which.*/
	int32 nodeID; 

	/* Store which other nodes point to THIS node */
	TArray<AAStarNode*> NodeArrayConnections;

	////////////////////////////////////////////////////////
	// HARD CODE

	AAStarNode* connection1 = nullptr;
	AAStarNode* connection2 = nullptr;
	AAStarNode* connection3 = nullptr;
	AAStarNode* connection4 = nullptr;
	AAStarNode* connection5 = nullptr;
	AAStarNode* connection6 = nullptr;
	AAStarNode* connection7 = nullptr;
	AAStarNode* connection8 = nullptr;


	//
	////////////////////////////////////////////////////////


	
	
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


	void GoCrazy();
	void LineTraceTest();

	void LineTraceMyOwn();

	// void SetConnection(class AAStarNode* connect, AAStarNode[]);


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
