// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "HealIngItemsComp.h"
#include "LightingItemsComp.h"
#include "SpeedItemComponet.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	if (HasPower)
		BatteryPower = 100;
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::UseItemWithPower()
{
	LightComp->ConsuPower = BatteryPowerCom;
	LightComp->OnLight();
}

void AItem::OnEffect()
{
	if (EffectTime > 0)
	{
		EffectTime -= 0.07f;
		SpeedComp->TimeOfEffect = EffectTime;
		SpeedComp->Use();

	}
	if (EffectTime < 0)
	{
		SpeedComp->EndEffect();
	}
}

void AItem::UseingBattery()
{
	if (LightComp == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Player don't pick up Light or find to get ref"), BatteryPower);
		return;
	}

	if (LightComp->isOn == true)
	{
		if(BatteryPower > 0)
			BatteryPower -= BatteryPowerCom;

		if (BatteryPower <= 0)
		{
			LightComp->ForsceOff();
			LightComp->isOn = false;
		}
	}
}

void AItem::UseItemOne()
{
	if (LightComp == nullptr)
	{
		return;
	}
	LightComp->Throwing();
}