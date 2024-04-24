// Fill out your copyright notice in the Description page of Project Settings.


#include "LightingItemsComp.h"
#include "GlowStickProjectila.h"
#include "Components/LightComponent.h"

// Sets default values for this component's properties
ULightingItemsComp::ULightingItemsComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULightingItemsComp::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ULightingItemsComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
/// <summary>
/// Throwing the itme
/// </summary>
void ULightingItemsComp::Throwing()
{
	AActor* a = GetWorld()->SpawnActor<AActor>(Projectile,los, FRotator(0, 0, 0));
}
/// <summary>
/// Forsce off light
/// </summary>
void ULightingItemsComp::ForsceOff()
{
	SorceLight->SetVisibility(false);
	isOn = false;
}
/// <summary>
/// Trun no light
/// </summary>
void ULightingItemsComp::OnLight()
{
	if (isProjectile == true)
		Throwing();

	if (isOn == true)
	{
		OFFLight();
		return;
	}

	isOn = true;
	SorceLight->SetVisibility(true);
}
/// <summary>
/// Trun off light
/// </summary>
void ULightingItemsComp::OFFLight()
{
	if (isOn == false)
	{
		OnLight();
		return;
	}

	isOn = false;
	SorceLight->SetVisibility(false);
}

