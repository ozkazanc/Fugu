#pragma once

#include "Test.h"

class Texture2DTest : public Test {
private:
		
	glm::mat4 m_Proj, m_View, m_Model;
	glm::vec3 m_ColorA, m_ColorB, m_PosA, m_PosB;

	std::shared_ptr<Fugu::VertexArray> m_VertexArray;
	std::shared_ptr<Fugu::Shader> m_Shader;
	std::shared_ptr<Fugu::Texture> m_Texture;

	std::shared_ptr<Fugu::OrthographicCamera> m_OrthoCamera;

public:
	Texture2DTest(const std::string& name = "Texture 2D Test");
	~Texture2DTest();

	virtual void OnUpdate(Fugu::Timestep ts) override;
	virtual void OnEvent(Fugu::Event& event) override;
	virtual void OnImGuiRender() override;
};