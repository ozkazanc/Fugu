#pragma once
#include "Fugu.h"

class ExampleLayer : public Fugu::Layer {
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Fugu::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Fugu::Event & e) override;

private:
	std::shared_ptr<Fugu::Shader> m_Shader;
	std::shared_ptr<Fugu::VertexArray> m_VertexArray;

	std::shared_ptr<Fugu::Shader> m_FlatColorShader;
	std::shared_ptr<Fugu::VertexArray> m_SquareVA;

	std::shared_ptr<Fugu::OrthographicCamera> m_OrthoCamera;
	//std::shared_ptr<Fugu::PerspectiveCamera> m_OrthoCamera;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};