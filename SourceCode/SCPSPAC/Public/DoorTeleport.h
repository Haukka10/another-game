// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorTeleport.generated.h"

UCLASS()
class SCPSPAC_API ADoorTeleport : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorTeleport();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Name of Level")
	FName LevelName = "";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Access level")
	uint8 AccessLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tele")
	bool IsTeleprt;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool OpenDoor(uint8 Level);

private:
	bool isMoving = false;
	bool isClose = false;

	float TimeToOpen = 0.7f;
	FVector OldLocation;
	
	void MoveDoor(FVector Loc);
	void CloseDoor();
};
