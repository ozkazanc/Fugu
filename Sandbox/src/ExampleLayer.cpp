#include "ExampleLayer.h"
#include "../../Fugu/vendor/imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
	:Layer("ExampleLayer")
{
	m_VertexArray.reset(Fugu::VertexArray::Create());

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	std::shared_ptr<Fugu::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(Fugu::VertexBuffer::Create(vertices, sizeof(vertices)));
	Fugu::BufferLayout layout = {
		{ Fugu::ShaderDataType::Float3, "a_Position" },
		{ Fugu::ShaderDataType::Float4, "a_Color" }
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[3] = { 0, 1, 2 };
	std::shared_ptr<Fugu::IndexBuffer> indexBuffer;
	indexBuffer.reset(Fugu::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_SquareVA.reset(Fugu::VertexArray::Create());

	float squareVertices[3 * 4] = {
		-0.75f, -0.75f, 0.0f,
		 0.75f, -0.75f, 0.0f,
		 0.75f,  0.75f, 0.0f,
		-0.75f,  0.75f, 0.0f
	};

	std::shared_ptr<Fugu::VertexBuffer> squareVB;
	squareVB.reset(Fugu::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ Fugu::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	std::shared_ptr<Fugu::IndexBuffer> squareIB;
	squareIB.reset(Fugu::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

	std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

	m_Shader.reset(Fugu::Shader::Create(vertexSrc, fragmentSrc));

	std::string flatColorrVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

	std::string flatColorFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

	m_FlatColorShader.reset(Fugu::Shader::Create(flatColorrVertexSrc, flatColorFragmentSrc));
}

void ExampleLayer::OnAttach() {}
void ExampleLayer::OnDetach() {}

void ExampleLayer::OnUpdate() {

	Fugu::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Fugu::RenderCommand::Clear();

	Fugu::Renderer::BeginScene();

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);
	Fugu::Renderer::Submit(m_SquareVA);

	m_Shader->Bind();
	Fugu::Renderer::Submit(m_VertexArray);

	Fugu::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void ExampleLayer::OnEvent(Fugu::Event& event) {
	if (event.GetEventType() == Fugu::EventType::KeyPressed) {
		Fugu::KeyPressedEvent& e = (Fugu::KeyPressedEvent&)event;

		if (e.GetKeyCode() == FG_KEY_TAB)
			FG_INFO("Tab key is pressed(event)!");

		FG_TRACE("{0}", (char)e.GetKeyCode());
	}
}