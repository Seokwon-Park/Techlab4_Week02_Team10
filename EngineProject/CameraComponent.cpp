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

    FQuat Q = transform.Rotation.Quaternion().Normalize();

    if (FInputSystem::IsKeyDown(EKeyCode::W))
    {
        transform.Location += Q.GetForwardVector() * CameraSpeed * DeltaTime;
    }
    if (FInputSystem::IsKeyDown(EKeyCode::A))
    {
        transform.Location -= Q.GetRightVector() * CameraSpeed * DeltaTime;
    }
    if (FInputSystem::IsKeyDown(EKeyCode::S))
    {
        transform.Location -= Q.GetForwardVector() * CameraSpeed * DeltaTime;
    }
    if (FInputSystem::IsKeyDown(EKeyCode::D))
    {
        transform.Location += Q.GetRightVector() * CameraSpeed * DeltaTime;
    }

    // if 마우스 키 다운이고 다른 클릭이 없다 이면
    //      마우스 키를 위치를 받아와서
    //      DeltaPitch Yaw에 저장

    if (FInputSystem::IsMouseDown(EMouseButton::Right))
    {
        float DeltaPitch = FInputSystem::GetMouseDeltaY() * MouseSensitivity;
        float DeltaYaw = FInputSystem::GetMouseDeltaX() * MouseSensitivity;

        FQuat DeltaQ = FRotator(DeltaPitch, DeltaYaw, 0.0f).Quaternion();
        FQuat Q = transform.Rotation.Quaternion().Normalize();
        FQuat Result = Q * DeltaQ;

        transform.Rotation = Result.ToFRotator(); ;
    }
    
    //FQuat NewQ = DeltaQ * Q;
    // ;

    // Yaw Pitch 를 입력을 통해 반환
    // DeltaQ는 입력을 통해 반환한 추가 회전을 쿼터니언으로 변환한 것
    // Q는 현재 카메라 컴포넌트의 로테이터 정보를 쿼터니언으로 변환한 것
    // NewQ = DeltaQ * Q
    // NewQ.ToFRotate -> 이걸 카메라 컴포넌트의 로테이터로 업데이트



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

FVector UCameraComponent::GetLocation()
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
    return GetWorldMatrix().Inverse();
}

FMatrix UCameraComponent::GetPerspectiveMatrix() const
{
	const float HalfFOV = FMath::DegreesToRadians(FOV) * 0.5f;

	const float YScale = 1.0f / tan(HalfFOV);
	const float XScale = YScale / AspectRatio;

	// Reversed-Z
	const float ZScale = -NearClipPlane / (FarClipPlane - NearClipPlane);
	const float ZOffset = NearClipPlane * FarClipPlane / (FarClipPlane - NearClipPlane);

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