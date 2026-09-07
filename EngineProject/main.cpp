#include "EnginePCH.h"

#include <Windows.h>
#include "Engine.h"

#include "Math/EngineMath.h"
#include <assert.h>
#define PI 3.141592f

int main()
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    TUniquePtr<Engine> engine = MakeUnique<Engine>();
    if (!engine->Init(hInstance)) return -1;

    engine->Run();
    engine->Shutdown();

	using namespace std;

	cout << fixed << setprecision(6);

	cout << "========================================\n";
	cout << "FQuat Debug Test\n";
	cout << "========================================\n\n";


	// ============================================================
	// 1. Identity
	// ============================================================

	cout << "[1] Identity\n";

	FQuat Identity = FQuat::Identity();

	cout << "X = " << Identity.X
		<< ", Y = " << Identity.Y
		<< ", Z = " << Identity.Z
		<< ", W = " << Identity.W << "\n\n";


	// ============================================================
	// 2. Axis Angle
	// Z축 90도 회전
	// ============================================================

	cout << "[2] MakeFromAxisAngle\n";

	const float HalfSqrt2 = 0.70710678118f;

	FQuat AxisAngle = FQuat::MakeFromAxisAngle(
		FVector(0.0f, 0.0f, 1.0f),
		PI * 0.5f
	);

	cout << "Expected : [0, 0, 0.707107, 0.707107]\n";
	cout << "Result   : ["
		<< AxisAngle.X << ", "
		<< AxisAngle.Y << ", "
		<< AxisAngle.Z << ", "
		<< AxisAngle.W << "]\n\n";


	// ============================================================
	// 3. Normalize
	// ============================================================

	cout << "[3] Normalize\n";

	FQuat Q(1.0f, 2.0f, 3.0f, 4.0f);

	cout << "Original : ["
		<< Q.X << ", "
		<< Q.Y << ", "
		<< Q.Z << ", "
		<< Q.W << "]\n";

	FQuat Normalized = Q.Normalize();

	cout << "Normalized : ["
		<< Normalized.X << ", "
		<< Normalized.Y << ", "
		<< Normalized.Z << ", "
		<< Normalized.W << "]\n";

	cout << "Length = "
		<< sqrtf(
			Normalized.X * Normalized.X +
			Normalized.Y * Normalized.Y +
			Normalized.Z * Normalized.Z +
			Normalized.W * Normalized.W
		)
		<< "\n\n";


	// ============================================================
	// 4. Conjugate
	// ============================================================

	cout << "[4] Conjugate\n";

	FQuat Conjugate = Q.Conjugate();

	cout << "Original  : ["
		<< Q.X << ", "
		<< Q.Y << ", "
		<< Q.Z << ", "
		<< Q.W << "]\n";

	cout << "Conjugate : ["
		<< Conjugate.X << ", "
		<< Conjugate.Y << ", "
		<< Conjugate.Z << ", "
		<< Conjugate.W << "]\n\n";


	// ============================================================
	// 5. Inverse
	// ============================================================

	cout << "[5] Inverse\n";

	FQuat Inverse = Q.Inverse();

	cout << "Inverse : ["
		<< Inverse.X << ", "
		<< Inverse.Y << ", "
		<< Inverse.Z << ", "
		<< Inverse.W << "]\n";

	FQuat IdentityCheck = Q * Inverse;

	cout << "Q * Q^-1 : ["
		<< IdentityCheck.X << ", "
		<< IdentityCheck.Y << ", "
		<< IdentityCheck.Z << ", "
		<< IdentityCheck.W << "]\n";

	cout << "Expected  : [0, 0, 0, 1]\n\n";


	// ============================================================
	// 6. Quaternion Multiplication
	// Z축 90도 * Z축 90도 = Z축 180도
	// ============================================================

	cout << "[6] Quaternion Multiplication\n";

	FQuat Q90 = FQuat::MakeFromAxisAngle(
		FVector(0.0f, 0.0f, 1.0f),
		PI * 0.5f
	);

	FQuat Q180 = Q90 * Q90;

	cout << "Q90  : ["
		<< Q90.X << ", "
		<< Q90.Y << ", "
		<< Q90.Z << ", "
		<< Q90.W << "]\n";

	cout << "Q180 : ["
		<< Q180.X << ", "
		<< Q180.Y << ", "
		<< Q180.Z << ", "
		<< Q180.W << "]\n";

	cout << "Expected: [0, 0, 1, 0]\n\n";


	// ============================================================
	// 7. Quaternion -> Matrix
	// ============================================================

	cout << "[7] ToFMatrix\n";

	FMatrix RotationMatrix = Q90.ToFMatrix();

	cout << "Rotation Matrix:\n";

	for (int Row = 0; Row < 4; ++Row)
	{
		cout << "[ ";

		for (int Col = 0; Col < 4; ++Col)
		{
			cout << setw(10)
				<< RotationMatrix.M[Row][Col]
				<< " ";
		}

		cout << "]\n";
	}

	cout << "\n";


	// ============================================================
	// 8. Euler
	// Pitch = 0
	// Yaw   = 90
	// Roll  = 0
	//
	// 현재 MakeFromEuler가 라디안 입력이라는 전제
	// ============================================================

	cout << "[8] MakeFromEuler\n";

	FQuat EulerQuat = FQuat::MakeFromEuler(
		0.0f,
		PI * 0.5f,
		0.0f
	);

	cout << "Euler Quaternion : ["
		<< EulerQuat.X << ", "
		<< EulerQuat.Y << ", "
		<< EulerQuat.Z << ", "
		<< EulerQuat.W << "]\n";

	cout << "Expected          : [0, 0, 0.707107, 0.707107]\n\n";


	// ============================================================
	// 9. Rotate Vector
	// +X -> +Y
	// Z축 90도 회전
	// ============================================================

	cout << "[9] RotateVector\n";

	FVector Forward(1.0f, 0.0f, 0.0f);

	cout << "Input : ["
		<< Forward.X << ", "
		<< Forward.Y << ", "
		<< Forward.Z << "]\n";

	/*
		주의:
		현재 RotateVector()의 Qv 생성 코드는 잘못되어 있으므로
		그 부분을 아래처럼 수정해야 정상적으로 테스트 가능.
	*/

	FVector Rotated = Q90.RotateVector(Forward);

	cout << "Output : ["
		<< Rotated.X << ", "
		<< Rotated.Y << ", "
		<< Rotated.Z << "]\n";

	cout << "Expected: [0, 1, 0]\n\n";


	// ============================================================
	// 10. Euler / AxisAngle 비교
	// ============================================================

	cout << "[10] AxisAngle vs Euler\n";

	cout << "AxisAngle : ["
		<< Q90.X << ", "
		<< Q90.Y << ", "
		<< Q90.Z << ", "
		<< Q90.W << "]\n";

	cout << "Euler     : ["
		<< EulerQuat.X << ", "
		<< EulerQuat.Y << ", "
		<< EulerQuat.Z << ", "
		<< EulerQuat.W << "]\n\n";


	cout << "========================================\n";
	cout << "Debug Finished\n";
	cout << "========================================\n";

	return 0;

    
}

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//    LPSTR lpCmdLine, int nCmdShow)
//{
//    TUniquePtr<Engine> engine = MakeUnique<Engine>();
//    if (!engine->Init(hInstance)) return -1;
//
//    engine->Run();
//    engine->Shutdown();
//
//
//    return 0;
//}