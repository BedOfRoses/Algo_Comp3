// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarNode.h"
#include "AStarGraph.h" // second try. worked, by setting pointer in for-loop where it is used. might be a problem later on
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h" 


// Sets default values
AAStarNode::AAStarNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	/*NodeTwoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeTwoMesh"));
	NodeTwoMesh->SetupAttachment(RootComponent);*/

	/*NodeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("NodeSphere"));
	RootComponent = NodeSphere;*/



	NodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeMesh"));
	RootComponent = NodeMesh;
	
	/*NodeMesh->SetupAttachment(RootComponent);*/
	//NodeMesh->SetHiddenInGame(false);

}

// Called when the game starts or when spawned
void AAStarNode::BeginPlay()
{
	Super::BeginPlay();

	NodeLocation = GetActorLocation();

	//FVector SpawnPoint = FVector(0.0f,0.0f,0.0f);
	//SetActorLocation(SpawnPoint);
	//FMath::FRandRange(0.0f, 10.0f);

	//for (int i = 0; i < 10; i++)
	//{

	//	//GetWorld()->SpawnActor(this);
	//}

	//DrawDebugPoint(GetWorld(), NodeSphere->GetComponentLocation(), 300, FColor(52, 220, 239), true);
	// 
	
	// create node function
		// pointer
	
		// data
	AssignIndividualVertexStructs();
}

// Called every frame
void AAStarNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GoCrazy();

	timerToGoCrazy += DeltaTime;
	

	//LineTraceMyOwn();

	
	if(bTimeToGoCrazy && timerToGoCrazy > timeCheckToGoCrazy)
		GoCrazy();

}


void AAStarNode::GoCrazy()
{
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



void AAStarNode::LineTraceMyOwn()
{

	//DrawDebugLine(GetWorld(), NodeTwoMesh->GetRelativeLocation(), NodeMesh->GetRelativeLocation(), 
	//	FColor::Purple, true, -1, 0, 10);


	//FHitResult OutHit;

	////FVector Start = NodeMesh->GetRelativeLocation();
	//FVector Start = GetActorLocation();

	//FVector ForwardVector = GetActorForwardVector();

	////FVector End = NodeTwoMesh->GetRelativeLocation();
	//FVector End = NodeTwoMesh->GetRelativeLocation() - Start;

	//FCollisionQueryParams CollisionParams;

	//FVector StartToEnd = End - Start;

	//double DotProd = FVector::DotProduct(Start, End);

	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 10.f);

	//if(ActorLineTraceSingle(OutHit,Start,End,ECC_WorldStatic,CollisionParams))
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("The component being hit is: %s"),
	//		*OutHit.GetComponent()->GetName()));
	//}


}

void AAStarNode::AssignIndividualVertexStructs() // sara - inserting information into struct or reading information from it
{
	//just checking if struct can be reached
	//FString MessageToScreen = FString::SanitizeFloat(ForThisSphere.VertexID);
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *MessageToScreen);
	//}

	//can i add information to each individual struct?
	FString ObjectName = this->GetName();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, *ObjectName);
	}



	////here we should try to get the vector and insert into struct!
	//// accessing struct here to test if i can reach from star graph
	//// ForThisSphere.ForeignVertexVector_one = ForeignNode->
	//int32 WhoGetsPaths = FMath::RandRange(0, 4); // this is currently a counter ----------------- I think this needs to be in starGraph. Its the only way this pointer is going to work. omg
	//for (int i = 0; i < WhoGetsPaths; i++) //here we will add pointers to the OtherNode's locations in home-node
	//{
	//	AAStarGraph* ForeignNode; // does it want this to be in .h?
	//	ForeignNode->ForeignVertecisLocations;
	//	// add pointer to these elements in struct
	//	//InsertVectorLocationInHomeNode(VertecisDistances[i]);
	//	ForThisSphere.ForeignVertecVectorArray[i] = ForeignNode->ForeignVertecisLocations[i];
	//}

	//// can i read the information about foreign vertex locations now?
	//FString ForeignVertecisLocationsDisplayMessage = FString::SanitizeFloat(ForThisSphere.ForeignVertecVectorArray[0].X);
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Purple, *ForeignVertecisLocationsDisplayMessage);
	//}
}




void AAStarNode::LineTraceTest()
{
	FHitResult OutHit;

		FVector Start = GetActorLocation();

		Start.Z += 50.f;
		Start.X += 200.f;

		FVector ForwardVector = GetActorForwardVector();
		FVector End = ((ForwardVector * 500.f) + Start);

		FCollisionQueryParams CollisionParams;

		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 5);

		bool isHit = ActorLineTraceSingle(OutHit, Start, End, ECC_WorldStatic, CollisionParams);

		if (isHit) {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("The Comp being hit is: %s"),
					*OutHit.GetComponent()->GetName()));
			}
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