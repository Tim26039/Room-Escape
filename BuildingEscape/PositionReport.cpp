// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "PositionReport.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	// krijgt de naam van het game object
	FString Snaam = GetOwner()->GetName();

	// krijg de positie van het game object en zet het in een string
	FString Spositie = GetOwner()->GetActorLocation().ToString(); // wijk af lecture 60

	// print functie van unreal
	UE_LOG(LogTemp, Warning, TEXT("%s Positie is %s"), *Snaam, *Spositie); // de %s zegt waat de fstrings komen

}


// Called every frame
void UPositionReport::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

