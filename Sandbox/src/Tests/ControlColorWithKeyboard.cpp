#include "ControlColorWithKeyboard.h"

ControlColorWithKeyboardTest::ControlColorWithKeyboardTest(const std::string& name)
	:Test(name)
{
	m_Color[0] = 0.0f, m_Color[1] = 0.0f, m_Color[2] = 0.0f, m_Color[3] = 1.0f;
	m_Channels[0] = false, m_Channels[1] = false, m_Channels[2] = false;
}

void ControlColorWithKeyboardTest::OnUpdate(Fugu::Timestep ts) {

	if (Fugu::Input::IsKeyPressed(FG_KEY_W) || Fugu::Input::IsKeyPressed(FG_KEY_UP)) {
		const float increment = 0.25f * ts;
		for (auto i = 0; i < 3; i++) {
			if (m_Channels[i]) {
				m_Color[i] += increment;
				if (m_Color[i] > 1.0f)
					m_Color[i] = 1.0f;
			}
		}
	}

	else if (Fugu::Input::IsKeyPressed(FG_KEY_S) || Fugu::Input::IsKeyPressed(FG_KEY_DOWN)) {
		const float decrement = 0.25f * ts;
		for (auto i = 0; i < 3; i++) {
			if (m_Channels[i]) {
				m_Color[i] -= decrement;
				if (m_Color[i] < 0.0f)
					m_Color[i] = 0.0f;
			}
		}
	}

	Fugu::RenderCommand::SetClearColor({ m_Color[0], m_Color[1], m_Color[2], m_Color[3] });
	Fugu::RenderCommand::Clear();
}

void ControlColorWithKeyboardTest::OnEvent(Fugu::Event& e) {}

void ControlColorWithKeyboardTest::OnImGuiRender() {
	ImGui::Begin("Select channel and use up/down arrow keys to adjust color");

	ImGui::Checkbox("R", &m_Channels[0]);
	ImGui::Checkbox("G", &m_Channels[1]);
	ImGui::Checkbox("B", &m_Channels[2]);

	ImGui::Text("R: %d, G: %d, B: %d", int(255 * m_Color[0]), int(255 * m_Color[1]), int(255 * m_Color[2]));

	ImGui::End();
}