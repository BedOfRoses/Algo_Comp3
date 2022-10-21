// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarNode.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h" 


// Sets default values
AAStarNode::AAStarNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeMesh"));

	NodeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("NodeSphere"));
	//NodeSphere->SetHiddenInGame(false);

}

// Called when the game starts or when spawned
void AAStarNode::BeginPlay()
{
	Super::BeginPlay();
	
	//FVector SpawnPoint = FVector(0.0f,0.0f,0.0f);
	//SetActorLocation(SpawnPoint);
	//FMath::FRandRange(0.0f, 10.0f);

	//for (int i = 0; i < 10; i++)
	//{


	//	//GetWorld()->SpawnActor(this);
	//}



	//DrawDebugPoint(GetWorld(), NodeSphere->GetComponentLocation(), 300, FColor(52, 220, 239), true);
}

// Called every frame
void AAStarNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < 1000; i++)
	{




		double randomRangex = FMath::RandRange(-1000.0f, 1000.0f);
		double randomRangey = FMath::RandRange(-1000.0f, 1000.0f);
		double randomRangez = FMath::RandRange(-1000.0f, 1000.0f);
		FVector randLocation = FVector(randomRangex, randomRangey, randomRangez);
		SetActorLocation(randLocation);


		double randomSizeRangex = FMath::RandRange(-10.0f, 10.0f);
		double randomSizeRangey = FMath::RandRange(-10.0f, 10.0f);
		double randomSizeRangez = FMath::RandRange(-10.0f, 10.0f);
		FVector actorSize = FVector(randomSizeRangex, randomSizeRangey, randomSizeRangez);
		SetActorScale3D(actorSize);

		/*double randomXsin = FMath::RandRange(0.0f, 1.0f);
		double randomYsin = FMath::RandRange(0.0f, 1.0f);
		double randomZsin = FMath::RandRange(0.0f, 1.0f);
		double randomSinValx = FMath::Sin(randomXsin);
		double randomSinValy = FMath::Sin(randomYsin);
		double randomSinValz = FMath::Sin(randomZsin);
		FVector actorSizeSinusLinus = FVector(randomSinValx, randomSinValy, randomSinValz);*/



		//GetWorld()->SpawnActor(this);
	}



}

//void AAStarNode::DrawDebugLine
//(
//	const UWorld* InWorld,
//	FVector const& LineStart,
//	FVector const& LineEnd,
//	FColor const& Color,
//	bool bPersistentLines,
//	float LifeTime,
//	uint8 DepthPriority,
//	float Thickness
//) {
//
//
//}