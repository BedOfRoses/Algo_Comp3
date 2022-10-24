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
	
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* NodeTwoMesh;*/



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeSphere")
	class USphereComponent* NodeSphere;

	int32 nodeNumber;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void GoCrazy();
	void LineTraceTest();

	void LineTraceMyOwn();

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


};
