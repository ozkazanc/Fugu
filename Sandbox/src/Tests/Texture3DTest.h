#pragma once
#include "Test.h"

#include "glm/glm.hpp"
#include <memory>

class Texture3DTest : public Test
{
private:
	float m_Time = 0.0f;

	std::shared_ptr<Fugu::VertexArray> m_VertexArray;
	std::shared_ptr<Fugu::Shader> m_Shader;
	std::shared_ptr<Fugu::Texture> m_Texture;

	std::shared_ptr<Fugu::PerspectiveCamera> m_PersCamera;

public:
	Texture3DTest(const std::string& name = "Texture 3D Test");
	~Texture3DTest() = default;

	virtual void OnUpdate(Fugu::Timestep ts) override;
	virtual void OnEvent(Fugu::Event& e) override;
	virtual void OnImGuiRender() override;

};