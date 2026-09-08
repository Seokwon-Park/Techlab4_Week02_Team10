#pragma once

class FOutline
{
public:
	void SetTarget(USceneComponent* InTarget) { Target = InTarget; }
	USceneComponent* GetTarget() const { return Target; }
	FMesh* GetMesh() const { return Mesh.get(); }
	const FMatrix& GetWorldMatrix() const { return World; };
private:
	USceneComponent* Target = nullptr;
	FMatrix World;	// 선택된 개체의 월드 매트릭스를 따름

	TSharedPtr<FMesh> Mesh;
};