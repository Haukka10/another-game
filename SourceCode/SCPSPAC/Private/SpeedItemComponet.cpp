// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedItemComponet.h"

// Sets default values for this component's properties
USpeedItemComponet::USpeedItemComponet()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpeedItemComponet::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USpeedItemComponet::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
/// <summary>
/// Use Item
/// </summary>
void USpeedItemComponet::Use()
{
	HasEffect = true;
	NewSpeed = SetSpeed();
}

/// <summary>
/// Ending effect
/// </summary>
void USpeedItemComponet::EndEffect()
{
	HasEffect = false;
	NewSpeed = 0.0F;
}
/// <summary>
/// Set new speed in range {-100; 450}
/// </summary>
/// <returns></returns>
float USpeedItemComponet::SetSpeed()
{
	auto a = DefSpeed * 0.10F;
	auto b = FMath::Lerp(a, DefSpeed,TimeOfEffect);

	b = FMath::Clamp(b, -100, 450);

	return DefSpeed + b / 1.5F;
}

