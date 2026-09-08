#include "EnginePCH.h"
#include "ControlPanel.h"
#include "../CameraActor.h"
#include "../Component/CameraComponent.h"

bool FControlPanel::Init()
{



	return true;
}

void FControlPanel::AddActor(EPrimitiveType Type)
{
	FTransform Transform;
	AActor* Actor = World->SpawnActor(AActor::StaticClass(), &Transform);
	Actor->AddPrimitiveComponent(Type);

	UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(Actor->GetRootComponent());

	Actor->GetPrimitiveComponent()->SetMeshShader(Mesh, Shader);
	Actor->GetPrimitiveComponent()->SetMeshData(Primitive->GetMeshData());

	ActorNum++;
}


void FControlPanel::OnRender()
{
	ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_FirstUseEver);
	ImGui::Begin("Jungle Control Panel");
	
	ImGui::Text("Hello Jungle world");
	ImGui::Text("FPS: %.f",FPS);

	ImGui::Separator();
	ImGui::Combo("Actor", &SelectedIndex, Items, IM_ARRAYSIZE(Items));
	ImGui::SameLine();
	ImGui::Text("Primitive");
	//EngineTimer::GetDeltaTime();
	if (ImGui::SmallButton("Spawn")) { AddActor(static_cast<EPrimitiveType>(SelectedIndex)); }
	ImGui::SameLine();
	ImGui::InputInt("##N", &ActorNum, 0, 0, ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	ImGui::Text("Number of spawn");

	ImGui::Separator();
	// 씬 생성 세이브 로드

	ImGui::Separator();
	UCameraComponent* CamCom = World->GetMainCamera()->GetCameraComponent();

	ImGui::Checkbox("IsOrthogonal", &CamCom->bIsOrthogonal);


	FTransform* transform = CamCom->GetTransform();

	ImGui::SetNextItemWidth(240.0f);
	ImGui::InputFloat("##FOV", &CamCom->FOV);

	ImGui::SetNextItemWidth(80.0f);
	ImGui::InputFloat("##X", &transform->Location.X);
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80.0f);
	ImGui::InputFloat("##Y", &transform->Location.Y);
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80.0f);
	ImGui::InputFloat("##Z", &transform->Location.Z);
	ImGui::SameLine();
	ImGui::Text("Camera Location");

	ImGui::SetNextItemWidth(80.0f);
	ImGui::InputFloat("##Pitch", &transform->Rotation.Pitch);
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80.0f);
	ImGui::InputFloat("##Yaw", &transform->Rotation.Yaw);
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80.0f);
	ImGui::InputFloat("##Roll", &transform->Rotation.Roll);
	ImGui::SameLine();
	ImGui::Text("Camera Rotation");

	ImGui::End();
}
