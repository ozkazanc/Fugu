#pragma once

#include "Fugu.h"

#include "../../Fugu/vendor/imgui/imgui.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Test {
public:
	Test(const std::string& name = "Test")
		:m_DebugName(name)
	{}

	virtual ~Test() = default;
		
	virtual void OnUpdate(Fugu::Timestep ts) = 0;
	virtual void OnEvent(Fugu::Event& e) = 0;
	virtual void OnImGuiRender() = 0;

protected:
	const std::string m_DebugName;
};

class TestMenu : public Fugu::Layer {
protected:
	std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	Test* m_CurrentTest;

public:
	TestMenu()
		:m_CurrentTest(nullptr) {}
	
	~TestMenu() {}

	template <class T>
	void RegisterTest(const std::string& name) {
		m_Tests.push_back(std::make_pair(name, [name]() { return new T(name); }));
	}

	virtual void OnAttach() override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Fugu::Event& event) override;
	virtual void OnUpdate(Fugu::Timestep ts) override;
};
