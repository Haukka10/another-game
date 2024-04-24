// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpeedItemComponet.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCPSPAC_API USpeedItemComponet : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpeedItemComponet();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	float DefSpeed = 555.0f;
	float NewSpeed;
	float LerpTime;
	float TimeOfEffect;
	bool HasEffect;

	void Use();
	void EndEffect();

private:
	float SetSpeed();
};
