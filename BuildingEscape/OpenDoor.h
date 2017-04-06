// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	// Uproperty zorgt dat de float der ondere overals gezien kan worden zoals in unreal engine zelf in de detail tap
	UPROPERTY(VisibleAnywhere)
	float OpenAngle = -80.0f;

	// zorgt der voor dat je het overals kan veranderen
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.2f;

	float LastDoorOpenTime; // is de tijd die hij binnen krijgt van waarneerd die hem heeft geopend

	AActor* Owner; // zegt welk game object het is
	AActor* ActorThatOpens; // het gene dat het zegt wat het opent


	float GetTotalMassOfActorsOnPlate(); // krijg het totaale gewicht op de pressure plate
	
};
