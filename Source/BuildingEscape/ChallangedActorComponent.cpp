// Fill out your copyright notice in the Description page of Project Settings.


#include "ChallangedActorComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UChallangedActorComponent::UChallangedActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UChallangedActorComponent::BeginPlay()
{
	Super::BeginPlay();

	/** Pointer and Reference Trials */
	/*
	//UE_Logs Examples
	UE_LOG(LogTemp, Warning, TEXT("This is how you give a warning"));
	UE_LOG(LogTemp, Display, TEXT("This is how you text your gf"));
	UE_LOG(LogTemp, Error, TEXT("This is how you maliciously cause errors"));

	//Pointer Concept
	
	FString Nome = "Samy";
	FString* PtrNome = &Nome;
	
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Nome);
	UE_LOG(LogTemp, Warning, TEXT("%s"), PtrNome);
	UE_LOG(LogTemp, Warning, TEXT("%s"), **PtrNome);

	// Accessing Methods of a class
	UE_LOG(LogTemp, Warning, TEXT("%i"), Nome.Len());
	UE_LOG(LogTemp, Warning, TEXT("%i"), (*PtrNome).Len());
	UE_LOG(LogTemp, Warning, TEXT("%i"), PtrNome->Len());

	// References
	FString& Name = Nome;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Name);
	UE_LOG(LogTemp, Warning, TEXT("%i"), Name.Len());
	*/

	/** Chalange Print Objects Name and position*/
	
	FString ObjectName = (*GetOwner()).GetName();
	FVector ObjectPosition = GetOwner()->GetActorLocation();
	FString PositionString = ObjectPosition.ToString();

	UE_LOG(LogTemp, Warning, TEXT(" %s is at Location: %s"), *ObjectName, *PositionString);

}


// Called every frame
void UChallangedActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

