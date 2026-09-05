#include "../EnginePCH.h"
#include "CameraComponent.h"
#include "../InputSystem.h"


UCameraComponent::UCameraComponent()
{

}

void UCameraComponent::BeginPlay()
{

}

void UCameraComponent::TickComponent(float DeltaTime)
{
    if (FInputSystem::IsKeyPressed(EKeyCode::W))
    {
        Transform.X += CameraSpeed * DeltaTime;
    }
    if (FInputSystem::IsKeyPressed(EKeyCode::A))
    {
        Transform.Y -= CameraSpeed * DeltaTime;
    }
    if (FInputSystem::IsKeyPressed(EKeyCode::S))
    {
        Transform.X -= CameraSpeed * DeltaTime;
    }
    if (FInputSystem::IsKeyPressed(EKeyCode::D))
    {
        Transform.Y += CameraSpeed * DeltaTime;
    }

}

void UCameraComponent::SetTransform(FVector vector)
{
    Transform = vector;
}

void UCameraComponent::SetScale(FVector vector)
{
    Scale = vector;
}

void UCameraComponent::SetRotation(FVector vector)
{
    
}

void UCameraComponent::SetFOV(float FoV)
{
	FOV = FoV;
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

FVector UCameraComponent::GetTransform()
{
	return Transform;
}

FVector UCameraComponent::GetScale()
{
    return Scale;
}

FMatrix UCameraComponent::GetRotation()
{
    return Rotation;
}

FMatrix UCameraComponent::GetViewMatrix() const
{
    FMatrix WorldMatrix = FMatrix(
        Rotation.M[0][0] * Scale.X,
        Rotation.M[0][1] * Scale.X,
        Rotation.M[0][2] * Scale.X,
        0.0f,

        Rotation.M[1][0] * Scale.Y,
        Rotation.M[1][1] * Scale.Y,
        Rotation.M[1][2] * Scale.Y,
        0.0f,

        Rotation.M[2][0] * Scale.Z,
        Rotation.M[2][1] * Scale.Z,
        Rotation.M[2][2] * Scale.Z,
        0.0f,

        Transform.X,
        Transform.Y,
        Transform.Z,
        1.0f
    );

    return WorldMatrix.Inverse();
}

FMatrix UCameraComponent::GetProjectionMatrix() const
{
	const float HalfFOV = FOV * 0.5f;

	const float YScale = 1.0f / tan(HalfFOV);
	const float XScale = YScale / AspectRatio;

	// Reversed-Z
	const float C = -NearClipPlane / (FarClipPlane - NearClipPlane);
	const float D = NearClipPlane * FarClipPlane / (FarClipPlane - NearClipPlane);

	return FMatrix(
		0.0f, 0.0f, C, 1.0f,
		XScale, 0.0f, 0.0f, 0.0f,
		0.0f, YScale, 0.0f, 0.0f,
		0.0f, 0.0f, D, 0.0f
	);
}