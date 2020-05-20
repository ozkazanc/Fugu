#pragma once
#include "Test.h"

class ControlColorWithKeyboardTest : public Test {
private:
	float m_Color[4];
	bool m_Channels[3];

public:
	ControlColorWithKeyboardTest(const std::string& name = "Control color w/ keyboard");
	~ControlColorWithKeyboardTest() = default;

	virtual void OnUpdate(Fugu::Timestep ts) override;
	virtual void OnEvent(Fugu::Event& e) override;
	virtual void OnImGuiRender() override;
};
