#pragma once

class FOutline
{
public:
	void SetTarget(UPrimitiveComponent* InTarget) { Target = InTarget; }
	UPrimitiveComponent* GetTarget() const { return Target; }
	FMesh* GetMesh() const { return Target->GetMesh().get(); }
	const FMatrix& GetWorldMatrix() const { return Target->GetTransform()->GetWorldMatrix(); };
private:
	UPrimitiveComponent* Target = nullptr;

};