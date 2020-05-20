#pragma once
#include "Test.h"

class MoveAround : public Test
{
private:
	float m_Time = 0.0f;
	std::vector<glm::vec3> m_Models;

	std::shared_ptr<Fugu::VertexArray> m_VertexArray;
	std::shared_ptr<Fugu::Shader> m_Shader;
	std::shared_ptr<Fugu::Texture> m_Texture;

	std::shared_ptr<Fugu::PerspectiveCamera> m_PersCamera;

public:
	MoveAround(const std::string& name = "Move Around Test");
	~MoveAround() = default;

	virtual void OnUpdate(Fugu::Timestep ts) override;
	virtual void OnEvent(Fugu::Event& e) override;
	virtual void OnImGuiRender() override;

};