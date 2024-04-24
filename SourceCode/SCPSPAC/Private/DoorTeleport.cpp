// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorTeleport.h"
#include "Editor/EditorEngine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoorTeleport::ADoorTeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorTeleport::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ADoorTeleport::OpenDoor(uint8 Level)
{
	if(LevelName == "")
		return false;
	
	if (AccessLevel >= Level && IsTeleprt == true)
	{
		UGameplayStatics::OpenLevel(this, LevelName, TRAVEL_Absolute);
		return true;
	}

	if (Level == AccessLevel)
	{
		OldLocation = GetActorLocation();
		isMoving = true;
		return true;
	}

	return false;
}

void ADoorTeleport::MoveDoor(FVector Loc)
{
	Loc.Y += FMath::Lerp(0, 25, TimeToOpen);
	SetActorLocation(Loc);

	if (TimeToOpen <= 0)
	{
		isMoving = false;
		isClose = true;
	}
}

void ADoorTeleport::CloseDoor()
{
	SetActorLocation(OldLocation);
	isClose = false;
}

// Called every frame
void ADoorTeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isMoving == true)
	{
		TimeToOpen -= 0.015F;
		MoveDoor(GetActorLocation());
	}
	if (isClose == true)
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADoorTeleport::CloseDoor, 4.5F);
		TimeToOpen = 0.7f;;
	}
}

