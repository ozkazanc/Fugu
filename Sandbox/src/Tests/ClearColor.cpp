#include "ClearColor.h"

ClearColorTest::ClearColorTest(const std::string& name)
 :Test(name)
//,m_ClearColor {0.6f, 0.6f, 0.3f, 1.0f}
{
	m_ClearColor[0] = 0.6f, m_ClearColor[1] = 0.6f, m_ClearColor[2] = 0.3f, m_ClearColor[3] = 1.0f;
}
ClearColorTest::~ClearColorTest() {}

void ClearColorTest::OnUpdate(Fugu::Timestep ts) {
	Fugu::RenderCommand::SetClearColor({ m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3] });
	Fugu::RenderCommand::Clear();
}

void ClearColorTest::OnImGuiRender() {
	ImGui::Begin("Background Color (TAB to return to Test Menu.)");
	ImGui::ColorEdit4("Clear Color", m_ClearColor);
	ImGui::End();
}