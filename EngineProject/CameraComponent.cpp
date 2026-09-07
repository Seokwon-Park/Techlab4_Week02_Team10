#include "EnginePCH.h"
#include "Component/CameraComponent.h"
#include "InputSystem.h"

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

    if (FInputSystem::IsKeyPressed(EKeyCode::W))
    {
        transform.Location.X += CameraSpeed * DeltaTime;
    }
    if (FInputSystem::IsKeyPressed(EKeyCode::A))
    {
        transform.Location.Y -= CameraSpeed * DeltaTime;
    }
    if (FInputSystem::IsKeyPressed(EKeyCode::S))
    {
        transform.Location.X -= CameraSpeed * DeltaTime;
    }
    if (FInputSystem::IsKeyPressed(EKeyCode::D))
    {
        transform.Location.Y += CameraSpeed * DeltaTime;
    }


    // 뷰 행렬, 투영 행렬 갱신

}

void UCameraComponent::SetTransform(FVector vector)
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
	return transform.Location;
}

FVector UCameraComponent::GetScale()
{
    return transform.Scale;
}

FRotator UCameraComponent::GetRotation()
{
    return transform.Rotation;
}

FMatrix UCameraComponent::GetViewMatrix() const
{
    /*FMatrix RotationMatrix = transform.Rotation.RotationMatrix();

    fmatrix worldmatrix = fmatrix(
        rotationmatrix[0][0] * transform.scale.x,
        rotationmatrix[0][1] * transform.scale.x,
        rotationmatrix[0][2] * transform.scale.x,
        0.0f,

        rotationmatrix[1][0] * transform.scale.y,
        rotationmatrix[1][1] * transform.scale.y,
        rotationmatrix[1][2] * transform.scale.y,
        0.0f,

        rotationmatrix[2][0] * transform.scale.z,
        rotationmatrix[2][1] * transform.scale.z,
        rotationmatrix[2][2] * transform.scale.z,
        0.0f,

        transform.location.x,
        transform.location.y,
        transform.location.z,
        1.0f
    );*/

    return GetWorldMatrix().Inverse();
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

FMatrix UCameraComponent::GetViewProjectionMatrix() const
{
    return GetViewMatrix() * GetProjectionMatrix();
}