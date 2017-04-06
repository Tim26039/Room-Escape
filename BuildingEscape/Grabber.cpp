// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	FindPhysicsComponent();
	SetupInputComponent();

}

void UGrabber::FindPhysicsComponent()
{
	FString Naam = GetOwner()->GetName();

	// vind van het object physichandle die je in de bleuprints heb toegevoegd
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("De physicsHandle werkt"));
	}

	else
	{
		// krijg de naam en zet het als een error message neer
		UE_LOG(LogTemp, Error, TEXT("krijg de physicsHandle niet van %s"), *Naam);
	}
}

void UGrabber::SetupInputComponent()
{
	FString Naam = GetOwner()->GetName();

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("De inputComponent  werkt"));

		// vraag hier een functien aan die ik heb gemaakt in project settings zeg daarna waarneer die moet kijken of het klopt dan bij welk object en dan welke functie die moet aan roepen
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}

	else
	{
		// krijg de naam en zet het als een error message neer
		UE_LOG(LogTemp, Error, TEXT("krijg de physicsHandle niet van %s"), *Naam);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Error, TEXT("YEAHHHHHHH"));
	
	// Line trace en zie of we in het berijk van een actor is met een physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReacht();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		// het eerste van de grabcomponent is het component dan de naam none dan de locatie dat die moet pakken en dan de rotatie of die true of false is
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Error, TEXT("BOEEEEEEEEE"));

	PhysicsHandle->ReleaseComponent();
}


const FHitResult UGrabber::GetFirstPhysicsBodyInReacht()
{
	// Set de paramater op of die op simpel of complex moet zoeknen en wat die moet negeren(ons zelf)
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	// hit result zelfde als bij unity raychast hit
	FHitResult Hit;


	// zeg wat die moet ray casten
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation(), LineTraceEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);

	// Maak hier een pointer aan van het type actor en vraag van het opbject hit de actor op
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		FString SactorHit = ActorHit->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit is: %s"), *SactorHit);
	}

	return Hit;
}

FVector UGrabber::LineTraceEnd()
{
	FVector VplayerViewPointLocation;
	FRotator RplayerViewPointRotation;

	// krijg van de de wereld de player controller en daar van de player view point waar je de locatie en rotatie in moet zetten
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT VplayerViewPointLocation, OUT RplayerViewPointRotation);

//	FString  SplayerViewPointLocation = VplayerViewPointLocation.ToString();
//	FString SplayerViewPointRotation = RplayerViewPointRotation.ToString();

	//UE_LOG(LogTemp, Warning, TEXT(" Player view point is %s, %s"), *SplayerViewPointLocation, *SplayerViewPointRotation);

	FVector VlineTraceEnd = VplayerViewPointLocation + RplayerViewPointRotation.Vector() * Freach;

	return VlineTraceEnd;
}

FVector UGrabber::PlayerViewPointLocation()
{
	FVector VplayerViewPointLocation;
	FRotator RplayerViewPointRotation;

	// krijg van de de wereld de player controller en daar van de player view point waar je de locatie en rotatie in moet zetten
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT VplayerViewPointLocation, OUT RplayerViewPointRotation);

	return VplayerViewPointLocation;
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// als de physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd());
	}
}