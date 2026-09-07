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

    // if 마우스 키 다운이고 다른 클릭이 없다 이면
    //      마우스 키를 위치를 받아와서
    //      DeltaPitch Yaw에 저장

    if (FInputSystem::IsMousePressed(EMouseButton::Right))
    {
        float DeltaPitch = FInputSystem::GetMouseDeltaY() * MouseSensitivity;
        float DeltaYaw = FInputSystem::GetMouseDeltaX() * MouseSensitivity;

        FQuat DeltaQ = FRotator(DeltaPitch, DeltaYaw, 0.0f).Quaternion();
        FQuat Q = transform.Rotation.Normalize();

        transform.Rotation = Q * DeltaQ;
    }
    
    //FQuat NewQ = DeltaQ * Q;
    // ;

    // Yaw Pitch 를 입력을 통해 반환
    // DeltaQ는 입력을 통해 반환한 추가 회전을 쿼터니언으로 변환한 것
    // Q는 현재 카메라 컴포넌트의 로테이터 정보를 쿼터니언으로 변환한 것
    // NewQ = DeltaQ * Q
    // NewQ.ToFRotate -> 이걸 카메라 컴포넌트의 로테이터로 업데이트



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

FQuat UCameraComponent::GetRotation()
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