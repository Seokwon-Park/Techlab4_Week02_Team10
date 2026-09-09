#include "EnginePCH.h"
#include "PropertyPanel.h"

bool FPropertyPanel::Init() 
{
	//transform = new FTransform(FVector(), FVector(), FRotator());
	return true;
}


void FPropertyPanel::OnRender()
{
	ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_FirstUseEver);

	ImGui::Begin("Jungle Property Window");

	UPrimitiveComponent* Primitive = World->GetPickingPrimitive();
	FTransform transform = FTransform();
	
	if (Primitive)
	{
		transform = *(Primitive->GetTransform());
	}

	ImGui::SetNextItemWidth(80.0f);
	ImGui::InputFloat("##X", &transform.Location.X);
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80.0f);
	ImGui::InputFloat("##Y", &transform.Location.Y);
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80.0f);
	ImGui::InputFloat("##Z", &transform.Location.Z);
	ImGui::SameLine();
	ImGui::Text("Translation");

	ImGui::SetNextItemWidth(80.0f);
	ImGui::InputFloat("##Pitch", &transform.Rotation.Pitch);
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80.0f);
	ImGui::InputFloat("##Yaw", &transform.Rotation.Yaw);
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80.0f);
	ImGui::InputFloat("##Roll", &transform.Rotation.Roll);
	ImGui::SameLine();
	ImGui::Text("Rotation");

	ImGui::SetNextItemWidth(80.0f);
	ImGui::InputFloat("##sX", &transform.Scale.X);
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80.0f);
	ImGui::InputFloat("##sY", &transform.Scale.Y);
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80.0f);
	ImGui::InputFloat("##sZ", &transform.Scale.Z);
	ImGui::SameLine();
	ImGui::Text("Scale");

	ImGui::Separator();
	ImGui::SetNextItemWidth(100.0f);
	ImGui::Combo("##GizmoCombo", &GizmoSelectedIndex, GizmoItems, IM_ARRAYSIZE(GizmoItems));
	ImGui::SameLine();
	if (ImGui::Button("Mode Chamge", ImVec2(100.0f, 19.0f))) { Gizmo->SetMode(static_cast<EGizmoMode>(GizmoSelectedIndex)); }

	ImGui::SetNextItemWidth(100.0f);
	ImGui::Combo("##SpaceCombo", &SpaceSelectedIndex, SpaceItems, IM_ARRAYSIZE(SpaceItems));
	ImGui::SameLine();
	if (ImGui::Button("Space Chamge", ImVec2(100.0f, 19.0f))) { Gizmo->SetSpace(static_cast<EGizmoSpace>(SpaceSelectedIndex)); }

	ImGui::End();
}

FPropertyPanel::~FPropertyPanel()
{
	//delete transform;
}