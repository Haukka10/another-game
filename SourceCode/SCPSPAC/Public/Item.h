// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "HealIngItemsComp.h"
#include "SpeedItemComponet.h"
#include "LightingItemsComp.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"


UENUM(BlueprintType)
enum class EType : uint8
{
	None,
	Heal,
	Light,
	Speed,
	Access,
	EnergiSave
};

UCLASS()
class SCPSPAC_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Item Paramers")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Paramers")
	UStaticMesh* Model;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Paramers")
	UTexture2D* ImageItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Paramers")
	bool HasPower;

	UPROPERTY(EditAnywhere, Category = "Item Paramers")
	bool IsToUse;

	UPROPERTY(EditAnywhere, Category = "Item Paramers")
	bool IsUseOne = true;

	UPROPERTY(EditAnywhere, Category = "Item Paramers")
	float PickUpTime;

	UPROPERTY(EditAnywhere, Category = "Item Paramers")
	float BatteryPower;

	UPROPERTY(EditAnywhere, Category = "Item Paramers")
	FVector PosItemCam;

	UPROPERTY(EditAnywhere, Category = "Item Paramers")
	float BatteryPowerCom = 0;

	UPROPERTY(EditAnywhere, Category = "Item Paramers")
	uint8 Level = 0;

	UPROPERTY(EditAnywhere, Category = "Item Paramers")
	float UseTime = 0;

	UPROPERTY(EditAnywhere, Meta = (Bitmask, BitmaskEnum = "EType"))
	EType ItemTypes;

	float EffectTime = 10;

	void UseItemWithPower();
	void UseItemOne();
	void UseingBattery();
	void OnEffect();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Componets")
	class UHealIngItemsComp* HealComp = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Componets")
	class ULightingItemsComp* LightComp = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Componets")
	class USpeedItemComponet* SpeedComp = nullptr;

private:

	bool IsUseing = true;
};
