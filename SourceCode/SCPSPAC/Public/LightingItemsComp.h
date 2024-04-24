// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/LightComponent.h"
#include "LightingItemsComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCPSPAC_API ULightingItemsComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULightingItemsComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void OFFLight();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ULightComponent* SorceLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Projectile;

	UFUNCTION(BlueprintCallable)
	void Throwing();

	UFUNCTION(BlueprintCallable)
	void ForsceOff();

	void OnLight();

	float Power = 0;
	float ConsuPower = 0;
	bool isOn = false;

	FVector los;

private:
};
