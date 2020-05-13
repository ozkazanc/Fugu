#pragma once
#include "Test.h"

class ClearColorTest : public Test {
private:
	float m_ClearColor[4];

public:
	ClearColorTest(const std::string& name = "Clear Color Test");
	~ClearColorTest();

	void OnUpdate(Fugu::Timestep ts) override;
	void OnEvent(Fugu::Event& event) override;
	void OnImGuiRender() override;
};