#include "EnginePCH.h"
#include "PrimitiveComponent.h"
#include "../Renderer.h"

void UPrimitiveComponent::Render()
{
	// 렌더링 테스트용 임시 버텍스 버퍼, 인덱스 버퍼
    float vertices[] = {
        // 앞면 (Front, Z = -0.5)
        -0.5f, -0.5f, -0.5f, // 0: 좌하단
         0.5f, -0.5f, -0.5f, // 1: 우하단
         0.5f,  0.5f, -0.5f, // 2: 우상단
        -0.5f,  0.5f, -0.5f, // 3: 좌상단

        // 뒷면 (Back, Z = 0.5)
        -0.5f, -0.5f,  0.5f, // 4: 좌하단
         0.5f, -0.5f,  0.5f, // 5: 우하단
         0.5f,  0.5f,  0.5f, // 6: 우상단
        -0.5f,  0.5f,  0.5f  // 7: 좌상단
    };

    unsigned int indices[] = {
        // 앞면 (Front)
        0, 3, 2,  2, 1, 0,
        // 뒷면 (Back)
        4, 5, 6,  6, 7, 4,
        // 왼쪽 면 (Left)
        4, 7, 3,  3, 0, 4,
        // 오른쪽 면 (Right)
        1, 2, 6,  6, 5, 1,
        // 윗면 (Top)
        3, 7, 6,  6, 2, 3,
        // 아랫면 (Bottom)
        4, 0, 1,  1, 5, 4
    };


    Mesh->Create(vertices, 8, indices, ARRAYSIZE(indices), 3);

	FRenderer::GetInstance().RenderPrimitive(
		Mesh->GetVertexBuffer(), Mesh->GetNumVertices(),
		Mesh->GetIndexBuffer(), Mesh->GetNumIndices(),		
		Mesh->GetStride());
	

}
