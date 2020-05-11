 #pragma once

#include "RenderCommand.h"
#include "Fugu/Renderer/Camera.h"
#include "Fugu/Renderer/Shader.h"

namespace Fugu {

	class Renderer {

	public:
		static void BeginScene(const Camera& camera);
		static void EndScene();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};
		static std::unique_ptr<SceneData> s_SceneData;
	};

}
