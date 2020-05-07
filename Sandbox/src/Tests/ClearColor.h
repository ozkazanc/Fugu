#pragma once
#include "Test.h"

class ColorClearTest : public Test {
private:
	float m_ClearColor[4];

public:
	ColorClearTest(const std::string& name = "Clear Color Test");
	~ColorClearTest();

	void OnUpdate() override;
	void OnImGuiRender() override;
};