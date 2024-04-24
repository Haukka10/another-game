// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "HealIngItemsComp.h"
#include "LightingItemsComp.h"
#include "SpeedItemComponet.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"
#include "Tasks/Task.h"
#include "Item.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	//if (GameInstanceSave->AvailableSaving)
	//	GameInstanceSave->SavingEQ(Items);
}

// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_SelectItemBuffor != nullptr && m_SelectItemBuffor->ItemTypes == EType::Light)
		m_SelectItemBuffor->UseingBattery();

	if (HasEffect && EffectItem->EffectTime >= 0)
	{
		EffectItem->OnEffect();
		MoveComp->MaxWalkSpeed = EffectItem->SpeedComp->NewSpeed;
	}
	else
	{
		EndOfEffect();
	}

	UpdatePickState();
}

void UEquipmentComponent::PickUPItem(AActor* Item)
{
	MoveComp->MaxWalkSpeed = 0.0f;
	if(auto ItemComp = Cast<AItem>(Item))
	{
		//Set up 
		TimerHadles = ItemComp->PickUpTime;
		m_Item = ItemComp;
		m_ActorItem = Item;

		//Select a comp
		switch (ItemComp->ItemTypes)
		{
			case EType::Light:
				ItemComp->LightComp = ItemComp->GetComponentByClass<ULightingItemsComp>();
				ItemComp->LightComp->Power = ItemComp->BatteryPower;
			break;

			case EType::Heal:
				ItemComp->HealComp = ItemComp->GetComponentByClass<UHealIngItemsComp>();
			break;

			case EType::Speed:
				ItemComp->SpeedComp = ItemComp->GetComponentByClass<USpeedItemComponet>();
				ItemComp->SpeedComp->HasEffect = HasEffect;
				EffectItem = m_Item;
			break;

			case EType::EnergiSave:
				m_Battery.Add(m_Item);
			break;
		}

		//Update timer
		UpdatePickState();
	}
}

void UEquipmentComponent::RemoveItmeFormEQ()
{
	auto S = m_SelectItemBuffor;

	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i]->Name == S->Name)
		{
			Items.RemoveAt(i);
			m_SelectItemBuffor = nullptr;
			Hand->SetStaticMesh(nullptr);

			return;
		}
	}
}

void UEquipmentComponent::OnOffLithgHitBox()
{

}

void UEquipmentComponent::SelectItem()
{
	// seft check && turn off light
	if (m_SelectItemBuffor != nullptr && m_SelectItemBuffor->LightComp != nullptr && m_SelectItemBuffor->IsUseOne == false)
		m_SelectItemBuffor->LightComp->ForsceOff();

	m_SelectItemBuffor = nullptr;

	if (Items.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("You don't have any items"));
		return;
	}

	if (Items.Num()-1 < IndexSelector)
		IndexSelector = 0;

	// Get a mesh for to a show a model
	if(Items[IndexSelector]->IsToUse)
	{
		Hand->SetStaticMesh(Items[IndexSelector]->Model);
		Hand->CastShadow = false;

		m_SelectItemBuffor = Items[IndexSelector];
	}
	else
	{
		return;
	}

	LevelBuffor = m_SelectItemBuffor->Level;
	IndexSelector++;
}

AItem* UEquipmentComponent::GetItemInHand()
{
	//if (m_SelectItemBuffor == nullptr)
	//	return nullptr;

	return m_SelectItemBuffor;
}

/// <summary>
/// Useing Items if you hold them
/// </summary>
void UEquipmentComponent::UseingItem()
{
	//seft check
	if (m_SelectItemBuffor == nullptr)
		return;

	//check if is a 1 time use item or not 
	if (m_SelectItemBuffor->IsUseOne == true && m_SelectItemBuffor->ItemTypes != EType::Speed)
	{
		m_SelectItemBuffor->LightComp->los = losCamera;
		m_SelectItemBuffor->UseItemOne();
		return;
	}

	if (EffectItem != nullptr && m_SelectItemBuffor->ItemTypes == EType::Speed)
	{
		EffectItem->SpeedComp->Use();
		HasEffect = EffectItem->SpeedComp->HasEffect;
		RemoveItmeFormEQ();
		return;
	}

	if(m_SelectItemBuffor->ItemTypes != EType::Access)
		m_SelectItemBuffor->UseItemWithPower();
}
void UEquipmentComponent::EndOfEffect()
{
	if (EffectItem == nullptr)
		return;

	EffectItem->SpeedComp->EndEffect();
	MoveComp->MaxWalkSpeed = 555.0F;
}
/// <summary>
/// Loading a battery for a light item 
/// </summary>
void UEquipmentComponent::LoadingBattery()
{
	UE_LOGFMT(LogTemp, Log, "Battery Left {0}", m_Battery.Num());

	for (int i = 0; i < m_Battery.Num(); i++)
	{
		if (m_SelectItemBuffor->BatteryPower >= 100)
			return;

		m_Battery.RemoveAt(i);
		m_SelectItemBuffor->BatteryPower = 100;

		if (m_Battery.Num() < 1)
			break;
	}
}

//void UEquipmentComponent::LoadItmes()
//{
//	Hand = nullptr;
//	Items = GameInstanceSave->ItmeToLoad();
//}

void UEquipmentComponent::UpdatePickState()
{
	if (TimerHadles > 0.01f)
		TimerHadles -= PickUpTimer;

	if (TimerHadles < 0.001f && m_Item != nullptr)
	{
		//Add to eq (List)
		if(m_Item->ItemTypes != EType::EnergiSave)
			Items.Add(m_Item);

		m_Item = nullptr;

		MoveComp->MaxWalkSpeed = 555.0f;
		m_ActorItem->Destroy();
	}
}