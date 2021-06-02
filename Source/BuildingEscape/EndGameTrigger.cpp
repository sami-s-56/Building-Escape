// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameTrigger.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BuildingEscapeGameModeBase.h"

// Sets default values for this component's properties
UEndGameTrigger::UEndGameTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEndGameTrigger::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UBoxComponent* CollisionComp = GetOwner()->FindComponentByClass<UBoxComponent>();
	if (CollisionComp) 
	{
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &UEndGameTrigger::OnPlayerEnter);
	}
}


// Called every frame
void UEndGameTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	
}

void UEndGameTrigger::OnPlayerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//call game mode end function after cecking door condition
	ABuildingEscapeGameModeBase* gameMode = Cast<ABuildingEscapeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gameMode)
	{
		gameMode->EndGame();
	}
}

