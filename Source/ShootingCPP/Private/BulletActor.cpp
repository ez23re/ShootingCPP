// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyActor.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	// 생성자 도우미를 이용해 에셋 로드하고 싶다
	ConstructorHelpers::FObjectFinder<UStaticMesh>Tempmesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	// 만약 로드가 성공했다면 그 에셋을 컴포넌트에 넣어주고 싶다
	if (Tempmesh.Succeeded()) {
		MeshComp->SetStaticMesh(Tempmesh.Object);
	}

	BoxComp->SetRelativeScale3D(FVector(0.75f, 0.25f, 1.0f));
	BoxComp->SetCollisionProfileName(TEXT("Bullet"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABulletActor::OnBulletOverlap);

}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector p0 = GetActorLocation();
	FVector velocity = GetActorForwardVector() * Speed;
	float t = DeltaTime;

	SetActorLocation(p0 + velocity * t);

}

void ABulletActor::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	if (enemy != nullptr) {
		OtherActor->Destroy();
	} this->Destroy();
}