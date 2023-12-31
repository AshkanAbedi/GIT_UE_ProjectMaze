// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "CharacterStates.h"
#include "PlayerCharacter.generated.h"

#pragma region Forward Declarations

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UCurveFloat;
class UCameraShakeSourceComponent;
class UTimelineComponent;
class ABullet;

#pragma endregion Forward Declarations

UCLASS()
class PROJECTMAZE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	EPlayerState PlayerState;

#pragma region Character Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera") TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera") TObjectPtr<UCameraComponent> MainCamera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera") TObjectPtr<UCameraShakeSourceComponent> CameraShakeSourceComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timeline") TObjectPtr<UCurveFloat> CameraZoomInCurve;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timeline") TObjectPtr<UCurveFloat> CameraZoomOutCurve;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timeline") TObjectPtr<UTimelineComponent> TimelineComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement") TObjectPtr<UCurveFloat> MovementSpeedCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon") TObjectPtr<USkeletalMeshComponent> WeaponSkeletalMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") TObjectPtr<USceneComponent> LaserPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") float LaserTraceDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet") TSubclassOf<ABullet> Bullet;

#pragma endregion Character Components

#pragma region Timer Handles

	FTimerHandle LaserTimerHandle;
	int32 LaserTimerCount = 0;
	
	FTimerHandle AimingTimerHandle;
	int32 AimingTimerCount = 0;

#pragma endregion Timer Handles

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma region EnhancedInput
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput") TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputMoveForward;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputMoveBackward;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputMoveRight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputMoveLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputLookAround;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputLookUp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputRun;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputAim;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputFire;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputChangeCameraAngle;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput") float LookUpSensitivity = 1.f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput") bool IsFiring = false;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput") bool IsRunning = false;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput") bool IsAiming = false;

#pragma endregion EnhancedInput

#pragma region Functions
	void StartMoveForward(const FInputActionInstance& Value);
	void StopMoveForward();
	void StartMoveBackward(const FInputActionInstance& Value);
	void StartMoveRight(const FInputActionInstance& Value);
	void StartMoveLeft(const FInputActionInstance& Value);
	void StartRun();
	void StopRun();
	void Turn(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void Fire(const FInputActionInstance& Value);
	void StopFire();
	void ChangeCameraAngle();
	void StartAim();
	void StopAim();
	void AimingTimer();
	void LaserTimer();
	UFUNCTION() void TimelineCameraZoomIn(const float Output) const;
	UFUNCTION() void TimelineCameraZoomOut(const float Output) const;
#pragma endregion Functions

private:
#pragma region Camera
	
	UPROPERTY(EditAnywhere, Category = "Camera") float MinPitch;
	UPROPERTY(EditAnywhere, Category = "Camera") float MaxPitch;
	UPROPERTY(EditAnywhere, Category = "Camera") float CurrentCameraBoomLength;
	UPROPERTY(EditAnywhere, Category = "Camera") float DefaultCameraBoomLength;
	UPROPERTY(EditAnywhere, Category = "Camera") float WalkingCameraBoomLength;
	UPROPERTY(EditAnywhere, Category = "Camera") float RunningCameraBoomLength;
	UPROPERTY(EditAnywhere, Category = "Camera") float CameraBoomInterpolationSpeed;
	
#pragma endregion Camera

#pragma region Tracing
	
	bool bHitSomething;
	FHitResult HitResult;
	FCollisionQueryParams LaserTraceParams;

#pragma endregion Tracing

public:
#pragma region Getter and Setters
	
	[[nodiscard]] bool HitSomething() const { return bHitSomething;}
	[[nodiscard]] FHitResult HitResult1() const{ return HitResult;}
	
#pragma endregion Getter and Setters
};
