#include "Texture3DTest.h"

Texture3DTest::Texture3DTest(const std::string& name)
	:Test(name)
{
	m_VertexArray.reset(Fugu::VertexArray::Create());

	float vertices[] = {
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, //3
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, //7

		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, //11
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, //15

		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, //19
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f  //23
	};

	std::shared_ptr<Fugu::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(Fugu::VertexBuffer::Create(vertices, sizeof(vertices)));
	Fugu::BufferLayout layout = {
		{ Fugu::ShaderDataType::Float3, "a_Position" },
		{ Fugu::ShaderDataType::Float2, "a_Texture"}
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	unsigned int indices[]{
		 0,  1,  2, //front
		 2,  3,  0,
		 4,  8, 11, //left
		11, 15,  4,
		21, 12, 23, //back
		23, 22, 21,
		 9, 13, 14, //right
		14, 10,  9,
		 6,  7, 19, //top
		19, 18,  6,
		17, 16, 20, //bottom
		20,  5, 17
	};

	std::shared_ptr<Fugu::IndexBuffer> indexBuffer;
	indexBuffer.reset(Fugu::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	std::string vertexSrc = R"(
		#version 330 core
		
		layout(location = 0) in vec3 aPos;
		layout(location = 1) in vec2 texCoord;
		
		out vec2 v_TexCoord;
		
		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;
		
		void main()
		{
			v_TexCoord = texCoord;
			gl_Position = u_ViewProjection * u_Transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}

	)";

	std::string fragmentSrc = R"(
			#version 330 core

			in vec2 v_TexCoord;

			uniform sampler2D u_TextureSlot;

			out vec4 fragColor;

			void main()
			{
				fragColor = texture(u_TextureSlot, v_TexCoord);
			}
		)";

	m_Shader.reset(Fugu::Shader::Create(vertexSrc, fragmentSrc));

	m_Texture.reset(Fugu::Texture2D::Create("res/textures/mario-question-block-128.png"));

	m_Texture->Bind();
	m_Shader->Bind();
	m_Shader->SetInt("u_TextureSlot", 0); // the slot id should be the same as the slot we bind our texture to

	float width = (float)Fugu::Application::GetInstance().GetWindow().GetWidth();
	float height = (float)Fugu::Application::GetInstance().GetWindow().GetHeight();
	m_PersCamera.reset(new Fugu::PerspectiveCamera(width / height));

	Fugu::Renderer::Init();
}

//Texture3DTest::~Texture3DTest() {
//	glDisable(GL_DEPTH_TEST);
//}

void Texture3DTest::OnUpdate(Fugu::Timestep ts) {
	m_Time += ts;
	m_PersCamera->OnUpdate(ts);

	Fugu::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Fugu::RenderCommand::Clear();

	Fugu::Renderer::BeginScene(*m_PersCamera);

	m_Texture->Bind();
	m_Shader->Bind();
	glm::mat4 m_Model = glm::rotate(glm::mat4(1.0f), m_Time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	Fugu::Renderer::Submit(m_Shader, m_VertexArray, m_Model);

	Fugu::Renderer::EndScene();
}

void Texture3DTest::OnEvent(Fugu::Event& e) {
	m_PersCamera->OnEvent(e);
}

void Texture3DTest::OnImGuiRender() {}