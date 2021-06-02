// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorOpener.generated.h"

UENUM(BlueprintType)
enum class EDoorType : uint8
{
	EDT_Rotating     UMETA(DisplayName = "Rotating"),
	EDT_Sliding      UMETA(DisplayName = "Sliding")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpener();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);

	void CloseDoor(float DeltaTime);

	float GetPressurePlateWeight();

	bool IsDoorOpen() { return bIsDoorOpen; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere, Category = "DoorSounds")
	USoundWave* OpenSound;

	UPROPERTY(EditAnywhere, Category = "DoorSounds")
	USoundWave* CloseSound;

	bool bPlayOpenSound = true;
	bool bPlayCloseSound = false;

	float currentYaw;
	FRotator DoorRotation;

	float currentHieght;
	FVector DoorPosition;

	UPROPERTY(VisibleAnywhere, Category = "InspectionVariables")	//todo remove
	bool bIsDoorOpen;

	UPROPERTY(EditAnywhere, Category = "DoorVariables")
		float DoorCloseDelay;

	UPROPERTY(EditAnywhere, Category = "DoorVariables")
		EDoorType DoorType;

	UPROPERTY(EditAnywhere, Category = "DoorVariables")
		float OpenYaw;

	UPROPERTY(EditAnywhere, Category = "DoorVariables")
		float ClosedYaw;

	UPROPERTY(EditAnywhere, Category = "DoorVariables")
		float OpenHeight;

	UPROPERTY(EditAnywhere, Category = "DoorVariables")
		float ClosedHeight;

	UPROPERTY(EditAnywhere, Category = "DoorVariables")
		float BaseRotatingSpeed = 45.f;

	UPROPERTY(EditAnywhere, Category = "DoorVariables")
		float BaseSlidingSpeed = 180.f;


	float currentDoorTime;

	UPROPERTY(EditAnywhere, Category = "Pressure Plate")
		class ATriggerVolume* pressurePlate;

	UPROPERTY(EditAnywhere, Category = "Pressure Plate")
		float PressureWeight;

	UPROPERTY(VisibleAnywhere, Category = "Pressure Plate")
		float WeightOnPlate;

	UPROPERTY()
	UAudioComponent* DoorAudio;

};
