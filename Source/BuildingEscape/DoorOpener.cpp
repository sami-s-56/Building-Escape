// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpener.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	// ...


	DoorRotation = GetOwner()->GetActorRotation();
	float currentYaw = DoorRotation.Yaw;

	DoorPosition = GetOwner()->GetActorLocation();
	float currentHieght = DoorPosition.Z;
	
	DoorAudio = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!DoorAudio) 
	{
		UE_LOG(LogTemp, Error, TEXT("DoorAudioComponent not found on %s"), *GetOwner()->GetName());
	}
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	/** Exponential Interpolation */
	/*currentYaw = FMath::Lerp(currentYaw, DoorRotation.Yaw + 90.f, 0.02f);
	currentYaw = FMath::FInterpTo(currentYaw, DoorRotation.Yaw + 90.f, DeltaTime, .2f);
	GetOwner()->SetActorRotation(FRotator(DoorRotation.Pitch, currentYaw, DoorRotation.Roll));*/

	if (GetPressurePlateWeight() >= PressureWeight)
	{
		bIsDoorOpen = true;
		OpenDoor(DeltaTime);
		currentDoorTime = (*GetWorld()).TimeSeconds;
	}
	else
	{
		bIsDoorOpen = false;
		if (GetWorld()->TimeSeconds >= currentDoorTime + DoorCloseDelay) 
		{
			CloseDoor(DeltaTime);
		}
	}

	
}

void UDoorOpener::OpenDoor(float DeltaTime)
{


	if (DoorType == EDoorType::EDT_Rotating) 
	{
		//*Linear Interpolation*/
		currentYaw = FMath::FInterpConstantTo(currentYaw, OpenYaw, DeltaTime, BaseRotatingSpeed);

		FRotator newRotation(DoorRotation.Pitch, currentYaw, DoorRotation.Roll);
		GetOwner()->SetActorRotation(newRotation);
	}
	else
	{
		currentHieght = FMath::FInterpConstantTo(currentHieght, OpenHeight, DeltaTime, BaseSlidingSpeed);

		FVector NewPosition(DoorPosition.X, DoorPosition.Y, currentHieght);
		GetOwner()->SetActorLocation(NewPosition);
	}

	if (DoorAudio && OpenSound)
	{
		if (bPlayOpenSound)
		{
			DoorAudio->SetSound(OpenSound);
			DoorAudio->Play();
			bPlayOpenSound = false;
			bPlayCloseSound = true;
		}
		else
		{
			return;
		}
	}

}

void UDoorOpener::CloseDoor(float DeltaTime)
{
	if (DoorType == EDoorType::EDT_Rotating)
	{
		//*Linear Interpolation*/
		currentYaw = FMath::FInterpConstantTo(currentYaw, ClosedYaw, DeltaTime, BaseRotatingSpeed * 3);

		FRotator newRotation(DoorRotation.Pitch, currentYaw, DoorRotation.Roll);
		GetOwner()->SetActorRotation(newRotation);
	}
	else
	{
		currentHieght = FMath::FInterpConstantTo(currentHieght, ClosedHeight, DeltaTime, BaseSlidingSpeed * 3);

		FVector NewPosition(DoorPosition.X, DoorPosition.Y, currentHieght);
		GetOwner()->SetActorLocation(NewPosition);
	}

	if (DoorAudio && CloseSound)
	{
		if (bPlayCloseSound)
		{
			DoorAudio->SetSound(CloseSound);
			DoorAudio->Play();
			bPlayOpenSound = true;
			bPlayCloseSound = false;
		}
		else
		{
			return;
		}
	}
}

float UDoorOpener::GetPressurePlateWeight()
{
	TArray<AActor*> overlappingActors;
	
	pressurePlate->GetOverlappingActors(overlappingActors);

	float mass = 0;

	for(AActor* _Actor : overlappingActors)
	{
		if (_Actor->FindComponentByClass<UPrimitiveComponent>()->GetCollisionObjectType() == ECollisionChannel::ECC_PhysicsBody) 
		{
			mass += _Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No physics body actor"));
		}
	}

	WeightOnPlate = mass;
	return mass;
}

