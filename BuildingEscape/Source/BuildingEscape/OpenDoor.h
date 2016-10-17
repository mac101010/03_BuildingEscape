/// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

/// dynamic delegate used to expose events to Blueprint  (for handling smooth door opening within Blueprint)
/// FDoorEvent is our own name for the event class node on Blueprint (name should resemble functionality)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	/// Sets default values for this component's properties
	UOpenDoor();

	/// Called when the game starts
	virtual void BeginPlay() override;
	
	/// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

private:

	AActor* Owner = GetOwner();

	/// this allows the value to be modified from within the editor
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 25.f;

	float GetTotalMassOfActorsOnPlate();
};
