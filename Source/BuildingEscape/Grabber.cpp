// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	/** Setting up physics handler and Input Component */
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	/** Validate Physics handle Component */
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Handle not set!"));
	}

	/** Validate Input Component */
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Component Found"));
		InputComponent->BindAction(TEXT("Grab"), IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction(TEXT("Grab"), IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component not Found!!"));
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/** If player is grabbing some object, update the position of object */
	if (PhysicsHandle->GetGrabbedComponent())
	{
		CalculateRaypoints();

		
		PhysicsHandle->SetTargetLocation(PlayerGrabPoint);
		
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Trying to grab..."));

	CalculateRaypoints();

	FHitResult HitResult =  GrabObjectInReach();

	GrabbedObject = HitResult.GetActor();

	/** If some object is hitted by raycast, attach it to physics handle */
	if (GrabbedObject) 
	{	
		if (GrabbedObject->ActorHasTag(FName("ToSteal")))
		{
			UE_LOG(LogTemp, Warning, TEXT("TagFound"));
			GrabbedObject->Destroy();
			GrabbedObject = nullptr;
			ObjectStolen++;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *GrabbedObject->GetName());

			UPrimitiveComponent* GrabbedComponent = HitResult.GetComponent();

			PhysicsHandle->GrabComponentAtLocation(GrabbedComponent, NAME_None, PlayerGrabPoint);

		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn`t reach any objects!"));
	}
}

FHitResult UGrabber::GrabObjectInReach()
{
	FHitResult RaycastResult;

	/** Raycast Description
	- Hit Result
	- Start and enc Location
	- collison type
	- extra parameters, hit object of some tag, use complex collision, actors to ignore
	*/

	/** Sample code for drawing debug line */
	/*DrawDebugLine(
		GetWorld(),
		PlayerViewpoint,
		PlayerGrabPoint,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.f
	);*/

	GetWorld()->LineTraceSingleByObjectType(RaycastResult, PlayerViewpoint, PlayerGrabPoint, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), FCollisionQueryParams(FName(""), false, GetOwner()));

	return RaycastResult;
}

void UGrabber::CalculateRaypoints()
{
	//Out parameters
	PlayerViewpoint;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewpoint, PlayerViewpointRotation);

	//Calculate End point
	FVector Direction = PlayerViewpointRotation.Vector();
	PlayerGrabPoint = PlayerViewpoint + (Direction * LineDistance);
}

void UGrabber::Release()
{
	//UE_LOG(LogTemp, Warning, TEXT("Releasing..."));

	if (PhysicsHandle->GetGrabbedComponent()) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Released %s"), *GrabbedObject->GetName());
		PhysicsHandle->ReleaseComponent();
		GrabbedObject = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You are holding nothing!!"));
	}
}