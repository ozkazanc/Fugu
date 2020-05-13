#include "Texture2DTest.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Texture2DTest::Texture2DTest(const std::string& name) 
	:Test(name),
	m_Proj(glm::mat4(1.0f)), m_View(glm::mat4(1.0f)), m_Model(glm::mat4(1.0f)),
	m_ColorA(1.0f), m_ColorB(1.0f), m_PosA(1.0f), m_PosB(1.0f),
	 m_VertexArray(nullptr),
	m_Texture(nullptr), m_Shader(nullptr)
{
	m_VertexArray.reset(Fugu::VertexArray::Create());
	
	float vertices[] = {
		-0.75f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.75f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.75f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.75f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	std::shared_ptr<Fugu::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(Fugu::VertexBuffer::Create(vertices, sizeof(vertices)));
	Fugu::BufferLayout layout = {
		{ Fugu::ShaderDataType::Float2, "a_Position" },
		{ Fugu::ShaderDataType::Float3, "a_Color"},
		{ Fugu::ShaderDataType::Float2, "a_Texture"}
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	unsigned int indices[]{
		0, 1, 2,
		2, 3, 0,
	};
	std::shared_ptr<Fugu::IndexBuffer> indexBuffer;
	indexBuffer.reset(Fugu::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	std::string vertexSrc = R"(
			#version 330 core

			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec3 aColor;
			layout (location = 2) in vec2 texCoord;

			out vec3 v_Color;
			out vec2 v_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
			   v_Color = aColor;
			   v_TexCoord = texCoord;
			   gl_Position = u_ViewProjection * u_Transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
			}
		)";

	std::string fragmentSrc = R"(
			#version 330 core

			in vec3 v_Color;
			in vec2 v_TexCoord;

			uniform vec3 u_Color;
			uniform sampler2D u_TextureSlot;

			out vec4 fragColor;

			void main()
			{
				//fragColor = vec4(v_Color, 1.0) + u_Color / 2.0;
				fragColor = texture(u_TextureSlot, v_TexCoord) + vec4(u_Color, 1.0f);
			}
		)";

	m_Shader.reset(Fugu::Shader::Create(vertexSrc, fragmentSrc));

	m_Texture.reset(Fugu::Texture2D::Create("res/textures/turkey-flag-icon-256.png"));
	//m_Texture.reset(Fugu::Texture2D::Create("res/textures/brazil-flag-icon-256.png")); 
	//m_Texture.reset(Fugu::Texture2D::Create("res/textures/OpenGL_170px_June16.png"));
		
	m_Texture->Bind();
	m_Shader->Bind();
	m_Shader->SetInt("u_TextureSlot", 0); // the slot id should be the same as the slot we bind our texture to

	uint32_t width = Fugu::Application::GetInstance().GetWindow().GetWidth();
	uint32_t height = Fugu::Application::GetInstance().GetWindow().GetHeight();
	m_OrthoCamera.reset(new Fugu::OrthographicCamera(width / 100, height / 100));

	m_PosA = glm::vec3(0.0f, 0.0f, 0.0f);
	m_PosB = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ColorA = glm::vec3(0.0f);
	m_ColorB = glm::vec3(0.0f);
}
Texture2DTest::~Texture2DTest() {}

void Texture2DTest::OnUpdate(Fugu::Timestep ts){
	m_OrthoCamera->OnUpdate(ts);

	Fugu::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Fugu::RenderCommand::Clear();

	Fugu::Renderer::BeginScene(*m_OrthoCamera);
	{
		// Render the first block			
		m_Texture->Bind();
		m_Shader->Bind();
		m_Shader->SetFloat3("u_Color", m_ColorA);
		Fugu::Renderer::Submit(m_Shader, m_VertexArray, glm::translate(glm::mat4(1.0f), m_PosA));
	}
	{
		// Render the second block
		m_Texture->Bind();
		m_Shader->Bind();
		m_Shader->SetFloat3("u_Color", m_ColorB);
		Fugu::Renderer::Submit(m_Shader, m_VertexArray, glm::translate(glm::mat4(1.0f), m_PosB));

	}
	Fugu::Renderer::EndScene();
}

void Texture2DTest::OnEvent(Fugu::Event& event) {
	m_OrthoCamera->OnEvent(event);
	if (event.GetEventType() == Fugu::EventType::WindowResize) {
		Fugu::WindowResizeEvent& e = static_cast<Fugu::WindowResizeEvent&>(event);
		m_OrthoCamera->SetWidthHeight(float(e.GetWidth()) / 100.0f, float(e.GetHeight()) / 100.0f);
	}
}

void Texture2DTest::OnImGuiRender(){
	ImGui::Begin("Texture 2D");
	float width = (float)Fugu::Application::GetInstance().GetWindow().GetWidth();
	float height = (float)Fugu::Application::GetInstance().GetWindow().GetHeight();
	width /= 100.0f;
	height /= 100.0f;
	ImGui::SliderFloat("XPositionA", &m_PosA.x, -width / 2.0f, width / 2.0f);
	ImGui::SliderFloat("YPositionA", &m_PosA.y, -height / 2.0f, height / 2.0f);
	ImGui::SliderFloat("XPositionB", &m_PosB.x, -width / 2.0f, width / 2.0f);
	ImGui::SliderFloat("YPositionB", &m_PosB.y, -height / 2.0f, height / 2.0f);

	ImGui::SliderFloat3("ColorA", glm::value_ptr(m_ColorA), -1.0f, 1.0f);
	ImGui::SliderFloat3("ColorB", glm::value_ptr(m_ColorB), -1.0f, 1.0f);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}