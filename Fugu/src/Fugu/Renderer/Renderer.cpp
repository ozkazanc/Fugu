#include "fgpch.h"
#include "Renderer.h"

namespace Fugu {
	
	std::unique_ptr<Renderer::SceneData> Renderer::s_SceneData = std::make_unique<Renderer::SceneData>();
	
	void Renderer::Init() {
		RenderCommand::Init();
	}
	void Renderer::BeginScene(const Camera& camera) {
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {
	
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::OnWindowResize(0, 0, width, height);
	}
		 
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform) {
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}