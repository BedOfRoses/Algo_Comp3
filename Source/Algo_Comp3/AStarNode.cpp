// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarNode.h"



// Sets default values
AAStarNode::AAStarNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	NodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeMesh"));
	RootComponent = NodeMesh;

	NodeMaterialBlue = CreateDefaultSubobject<UMaterial>(TEXT("NodeMaterialBlue"));
	NodeMaterialGreen = CreateDefaultSubobject<UMaterial>(TEXT("NodeMaterialGreen"));
	NodeMaterialOrange = CreateDefaultSubobject<UMaterial>(TEXT("NodeMaterialOrange"));
	
	bVisited = false;
	
	
}

// Called when the game starts or when spawned
void AAStarNode::BeginPlay()
{
	Super::BeginPlay();

	NodeLocation = GetActorLocation();
	
}

// Called every frame
void AAStarNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}