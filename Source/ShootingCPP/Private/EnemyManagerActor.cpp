// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerActor.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "EnemyActor.h"

// Sets default values
AEnemyManagerActor::AEnemyManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	Origin = CreateDefaultSubobject<UArrowComponent>(TEXT("Origin"));
	Origin->SetupAttachment(RootComponent);
	Origin->SetRelativeRotation(FRotator(-90.0f, 180.0f, 0.0f));
}

// Called when the game starts or when spawned
void AEnemyManagerActor::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemyManagerActor::EndPlay(const EEndPlayReason::Type EEndPlayReason)
{
	Super::EndPlay(EEndPlayReason);

}

// Called every frame
void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTime += DeltaTime;
	if (CurrentTime >= MakeTime) {
		auto Enemy = GetWorld()->SpawnActor<AEnemyActor>(EnemyFactory, Origin->GetComponentTransform());
		CurrentTime = 0.0f;
	}
}

void AEnemyManagerActor::MakeEnemy()
{
	FTransform t = Origin->GetComponentTransform();
	GetWorld()->SpawnActor<AEnemyActor>(EnemyFactory, t);
}

