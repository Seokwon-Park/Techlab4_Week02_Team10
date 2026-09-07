#include "EnginePCH.h"
#include "Picking.h"

FRay Picking::ScreenToRay(int32 MouseX, int32 MouseY, int32 ScreenWidth, int32 ScreenHeight, const FMatrix& View, const FMatrix& Proj)
{
	//float NdcX = 2.0f * MouseX / ScreenWidth - 1.0f;
	//float NdcY = 1.0f - 2.0f * MouseY / ScreenHeight;

	//FMatrix InvProjView = (View * Proj).Inverse();

	//FVector4 NearWorld = FVector4(NdcX, NdcY, 0.0f, 1.0f) * InvProjView;
	//FVector4 FarWorld= FVector4(NdcX, NdcY, 0.0f, 1.0f) * InvProjView;
	//NearWorld /= NearWorld.W;
	//FarWorld /= FarWorld.W;

	//FRay Ray;
	//Ray.Origin = FVector(NearWorld.X, NearWorld.Y, NearWorld.Z);
	//Ray.Direction = FVector(FarWorld.X, FarWorld.Y, FarWorld.Z) - Ray.Origin).Normalize();

	return FRay();
}
