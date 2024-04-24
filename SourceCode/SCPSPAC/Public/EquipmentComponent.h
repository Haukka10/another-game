// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"

#include "Item.h"
//#include "GameInstanceSaveing.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCPSPAC_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	uint8 IndexSelector = 0;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timer")
	float TimerHadles;

	UFUNCTION(BlueprintCallable, Category = "MainSystem")
	void UpdatePickState();

	UFUNCTION(BlueprintCallable, Category = "MainSystem")
	void PickUPItem(AActor* Item);

	UFUNCTION(BlueprintCallable, Category = "MainSystem")
	void SelectItem();

	UFUNCTION(BlueprintCallable, Category = "MainSystem")
	void UseingItem();

	UFUNCTION(BlueprintCallable, Category = "MainSystem")
	AItem* GetItemInHand();

	UFUNCTION(BlueprintCallable, Category = "MainSystem")
	void EndOfEffect();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainSystem")
	UStaticMeshComponent* Hand;

	class UCharacterMovementComponent* MoveComp;
	USkeletalMeshComponent* Player;

	void LoadingBattery();

	//void LoadItmes();

	uint8 LevelBuffor = 0;

	FVector losCamera;
private:

	AItem* m_Item;
	AItem* m_SelectItemBuffor;
	AActor* m_ActorItem;

	void RemoveItmeFormEQ();

	void OnOffLithgHitBox();

	AItem* EffectItem = nullptr;

	TArray<AItem*> m_Battery;

	TArray<AItem*> Items;

	float PickUpTimer = 0.2F;

	bool HasEffect = false;

protected:

};
