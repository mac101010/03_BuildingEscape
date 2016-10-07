/// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	/// Sets default values for this component's properties
	UOpenDoor();

	/// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();
	
	/// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
private:

	AActor* Owner = GetOwner();

	/// UPROPERTY has strict syntax requirements (has to be immediately above the variable that it's targeting, no whitespace)
	UPROPERTY(EditAnywhere)
	float OpenAngle = 0.0f;

	/// this allows the value to be modified from within the editor
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.75f;

	float LastDoorOpenTime;
};
