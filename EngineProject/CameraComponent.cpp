#include "EnginePCH.h"
#include "Component/CameraComponent.h"
#include "InputSystem.h"
#include "Ray.h"

//UCameraComponent::UCameraComponent()
//{
//
//}

void UCameraComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UCameraComponent::TickComponent(float DeltaTime)
{
    Super::TickComponent(DeltaTime);

    FQuat Q = transform.Rotation.Quaternion().Normalize();

    if (FInputSystem::IsKeyDown(EKeyCode::W))
    {
        transform.Location += transform.GetForward() * CameraSpeed * DeltaTime;
    }
    if (FInputSystem::IsKeyDown(EKeyCode::A))
    {
        transform.Location -= transform.GetRight() * CameraSpeed * DeltaTime;
    }
    if (FInputSystem::IsKeyDown(EKeyCode::S))
    {
        transform.Location -= transform.GetForward() * CameraSpeed * DeltaTime;
    }
    if (FInputSystem::IsKeyDown(EKeyCode::D))
    {
        transform.Location += transform.GetRight() * CameraSpeed * DeltaTime;
    }
    if (FInputSystem::IsKeyDown(EKeyCode::Q))
    {
        transform.Location += transform.GetUp() * CameraSpeed * DeltaTime;
    }
    if (FInputSystem::IsKeyDown(EKeyCode::E))
    {
        transform.Location -= transform.GetUp() * CameraSpeed * DeltaTime;
    }

    if (FInputSystem::IsMouseDown(EMouseButton::Right))
    {
        float DeltaPitch = -FInputSystem::GetMouseDeltaY() * MouseSensitivity;
        float DeltaYaw = -FInputSystem::GetMouseDeltaX() * MouseSensitivity;

        transform.Rotation.Pitch -= DeltaPitch;
        transform.Rotation.Yaw -= DeltaYaw;
    }

    int32 WDelta = FInputSystem::GetWheelDelta();

    if (WDelta > 0)
    {
        transform.Location += transform.GetForward() * WheelSpeed * WDelta * DeltaTime;
    }

    if (WDelta < 0)
    {
        transform.Location += transform.GetForward() * WheelSpeed * WDelta* DeltaTime;
    }


    /*if (FInputSystem::IsMouseDown(EMouseButton::Left))
    {
        FVector RayDirection = DeProjection(FInputSystem::GetMouseX(), FInputSystem::GetMouseY());

        printf(
            "Ray Direction: X=%f Y=%f Z=%f\n",
            RayDirection.X,
            RayDirection.Y,
            RayDirection.Z
        );
    }*/
}

void UCameraComponent::SetLocation(FVector vector)
{
    transform.Location = vector;
}

void UCameraComponent::SetScale(FVector vector)
{
    transform.Scale = vector;
}

//void UCameraComponent::SetRotation(FVector vector)
//{
//    
//}

void UCameraComponent::SetFOV(float FoV)
{
	FOV = FoV;
}

float* UCameraComponent::GetFOV()
{
    return &FOV;
}

void UCameraComponent::SetAspectRatio(float Ratio)
{
	AspectRatio = Ratio;
}

void UCameraComponent::SetNearClipPlane(float NearPlane)
{
	NearClipPlane = NearPlane;
}

void UCameraComponent::SetFarClipPlane(float FarPlane)
{
	FarClipPlane = FarPlane;
}

FVector UCameraComponent::GetLocation() const
{
	return transform.Location;
}

FVector UCameraComponent::GetScale() const
{
    return transform.Scale;
}

FRotator UCameraComponent::GetRotation() const
{
    return transform.Rotation;
}

FRay UCameraComponent::DeProjection(int32 MouseX, int32 MouseY)
{
    FVector COP = transform.Location;

    // 1280 720

    const float NDCX = 2.0f * MouseX / 1280 - 1.0f;
    const float NDCY = 1.0f - 2.0f * MouseY / 720;

    // Near Plane 위의 점
    FVector4 NDCPoint(NDCX, NDCY, 1.0f, 1.0f);
    FVector4 CameraPoint = NDCPoint * GetPerspectiveMatrix().Inverse();
    CameraPoint /= CameraPoint.W;

    FVector4 WorldPoint = CameraPoint * GetViewMatrix().Inverse();
    WorldPoint /= WorldPoint.W;

    FRay ray;
    ray.Origin = transform.Location;
    ray.Direction = (FVector(WorldPoint.X, WorldPoint.Y, WorldPoint.Z) - ray.Origin).Normalize();

    return ray;
}

FMatrix UCameraComponent::GetViewMatrix() const
{
    return GetWorldMatrix().Inverse();
}

FMatrix UCameraComponent::GetPerspectiveMatrix() const
{
	const float HalfFOV = FMath::DegreesToRadians(FOV) * 0.5f;

	const float YScale = 1.0f / tan(HalfFOV);
	const float XScale = YScale / AspectRatio;

    const float ZScale = FarClipPlane / (FarClipPlane - NearClipPlane);
    const float ZOffset = -NearClipPlane * FarClipPlane /(FarClipPlane - NearClipPlane);

	return FMatrix(
		0.0f, 0.0f, ZScale, 1.0f,
		XScale, 0.0f, 0.0f, 0.0f,
		0.0f, YScale, 0.0f, 0.0f,
		0.0f, 0.0f, ZOffset, 0.0f
	);
}

FMatrix UCameraComponent::GetOrthogonalMatrix() const
{
    const float Width = OrthoWidth;
    const float Height = Width / AspectRatio;

    const float XScale = 2.0f / Width;
    const float YScale = 2.0f / Height;

    const float ZScale = 1.0f / (FarClipPlane - NearClipPlane);
    const float ZOffset = -NearClipPlane / (FarClipPlane - NearClipPlane);

    return FMatrix(
        0.0f, 0.0f, ZScale, 0.0f,
        XScale, 0.0f, 0.0f, 0.0f,
        0.0f, YScale, 0.0f, 0.0f,
        0.0f, 0.0f, ZOffset, 1.0f
    );
}

FMatrix UCameraComponent::GetViewProjectionMatrix() const
{
    if (bIsOrthogonal)
        return GetViewMatrix() * GetOrthogonalMatrix();
    
    return GetViewMatrix() * GetPerspectiveMatrix();
}