/// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

/// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	/// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	/// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	/// ...
}


/// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pressure plate unassigned"));
	}
}

/// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorsOnPlate() >= TriggerMass)
		OnOpen.Broadcast();
	else
		OnClose.Broadcast();
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	TArray<AActor*> OverlappingActors;

	if (!PressurePlate) { return -1; }

	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	float TotalMass = 0;
	for (const auto& CurrentActor : OverlappingActors)
	{
		float CurrentActorMass = CurrentActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		TotalMass += CurrentActorMass;

		UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *CurrentActor->GetName());
	}

	UE_LOG(LogTemp, Warning, TEXT("TOTAL: %f"), TotalMass);

	return TotalMass;
}

