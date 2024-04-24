// Fill out your copyright notice in the Description page of Project Settings.


#include "OnAttakCharaterAI.h"

// Sets default values for this component's properties
UOnAttakCharaterAI::UOnAttakCharaterAI()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOnAttakCharaterAI::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOnAttakCharaterAI::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UOnAttakCharaterAI::CanAttackCharater()
{
	UE_LOG(LogTemp, Display, TEXT("Can Attack"));

}

