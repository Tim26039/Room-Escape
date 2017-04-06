// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:

	float Freach = 100.f;

	// Maak een pointer van de klas UphysicsHandleComponent en verwijs hem na niks De U staat voor de classes van components types
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Ray-cast en pak het waarneer het in de buurt is
	void Grab();

	// word opgeroepen waarneer het word losgelaten
	void Release();

	// vind de physics handel die er aan gekoppeld is
	void FindPhysicsComponent();

	//Setup input component
	void SetupInputComponent();

	// return hit voor physic body in reach
	const FHitResult GetFirstPhysicsBodyInReacht();

	FVector LineTraceEnd();

	FVector PlayerViewPointLocation();

};
