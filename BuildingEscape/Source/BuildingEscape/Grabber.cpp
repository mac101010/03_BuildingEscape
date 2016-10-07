/// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

/// macro preprocessor directive for identifier and replacement (i.e. cut and paste) (currently empty)
#define OUT


/// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


/// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	
}


/// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

	///UE_LOG(LogTemp, Warning, TEXT("Location: %s; Rotation: %s"), 
	///	*PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	/// .Vector() converts to unit vector (magnitude of 1)
	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

	/// global function from DrawDebugHelpers class
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255,0,0),
		false,
		0.f,
		0.f,
		10.f
	);

	/// 1st param =  name, 2nd param = bool to do trace based on complex collision, 3rd param = actor to ignore (should be self)
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;

	/// remember that prefix 'E' is enum
	/// this function call will put into 'Hit' all 'ECC_PhysicsBody' collision actors (e.g. the chair and table)
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor* ActorHit = Hit.GetActor();

	if (ActorHit && !bActorAlreadyDetected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *ActorHit->GetName());
		bActorAlreadyDetected = true;
	}
	else if (!ActorHit && bActorAlreadyDetected)
		bActorAlreadyDetected = false;
}

