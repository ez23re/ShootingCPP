// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "BulletActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Box, Mesh, Arrow 생성
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);

	FirePositionComp = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePositionComp"));
	FirePositionComp->SetupAttachment(RootComponent);
	FirePositionComp->SetRelativeLocationAndRotation(FVector(0.0f,0.0f,100.0f),FRotator(90.0f,0.0f,0.0f));

	// 오버랩 이벤트 On
	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComp->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	BoxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);

	BoxComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector dir = FVector(0.0f, h, v);
	dir.Normalize();

	FVector p0 = GetActorLocation();
	FVector velocity = dir * Speed;

	SetActorLocation(p0 + velocity * DeltaTime, true);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// BindAxis
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerPawn::OnAxisHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerPawn::OnAxisVertical);

	// BindAction
	//PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, &APlayerPawn::OnActionFire);

}

void APlayerPawn::OnAxisHorizontal(float value)
{
	h = value;
}

void APlayerPawn::OnAxisVertical(float value)
{
	v = value;
}

void APlayerPawn::OnActionFire()
{
	// Click시 총알 이동시키기
	FTransform FirePos = FirePositionComp->GetComponentTransform();
	GetWorld()->SpawnActor<ABulletActor>(BulletFactory, FirePos);
}
