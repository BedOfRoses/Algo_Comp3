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
	

	/* to indentify which node is which.*/
	int32 nodeID; 

	/* Store which other nodes point to THIS node */
	UPROPERTY(EditAnywhere, Category = "NodeArrayConnectios")
	TArray<AAStarNode*> NodeArrayConnections;
	
	UPROPERTY(EditAnywhere, Category = "Node Cost")
	float Cost = 0;

	bool bVisited;
	
	FVector NodeLocation;

	
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};


