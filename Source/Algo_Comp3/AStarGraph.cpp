// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarGraph.h"
#include "AStarNode.h"
#include "Components/BoxComponent.h"

// Sets default values
AAStarGraph::AAStarGraph()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	RootComponent = BoxComponent;

}

// Called when the game starts or when spawned
void AAStarGraph::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AAStarGraph::OnOverlap);

	//BoxComponent->OnComponentBeginOverlap.__Internal_AddDynamic(this, &AAStarGraph::OnOverlap);

	BoxScan();

	//NodesArray.Init(AStarNode, 8);
	
}

// Called every frame
void AAStarGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//BoxScan();

}


void AAStarGraph::BoxScan()
{
	
	//FVector BoxSize = GetActorBounds();
	FVector ActorScale = GetActorScale();

	bool isBoxBigEnough = false;

	if (isBoxBigEnough == false) 
	{
		for (float i = 0.f; i < 10.f; i++)
		{
			SetActorScale3D(FVector(i, i, i));
		}
		isBoxBigEnough = true;
	}
	


}





void AAStarGraph::OnOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent,
	int32 OtherbodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{

	//if(OtherActor->IsA(AAStarNode::StaticClass()))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Hit AStarNode"))

	//	/*if (GEngine) {
	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("DebugTest"));
	//	}*/
	//
	//}

	UE_LOG(LogTemp, Warning, TEXT("Hit AStarNode"))



}