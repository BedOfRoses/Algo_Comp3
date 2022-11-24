// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "AlgoWidget.generated.h"

class AAStarGraph;
/**
 * 
 */
UCLASS()
class ALGO_COMP3_API UAlgoWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UAlgoWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClickButtonDijkstra();

	UFUNCTION()
	void OnClickButtonTravelMan();

	UFUNCTION()
	void OnClickButtonAStar();

	UPROPERTY(meta=(BindWidget))
	UButton* DijkstraButton;
	
	UPROPERTY(meta=(BindWidget))
	UButton* TravelManButton;

	UPROPERTY(meta=(BindWidget))
	UButton* AStarButton;


	

	

	AAStarGraph* graph = nullptr;
	
	
};
