#pragma once

#include "Fugu.h"
#include "../../Fugu/vendor/imgui/imgui.h"

class Test : public Fugu::Layer {
public:
	Test(const std::string& name = "Test")
		:m_DebugName(name), 
		Layer(name) {}

	virtual ~Test() {}
		
	virtual void OnUpdate() override {}
	virtual void OnEvent(Fugu::Event& e) override {}
	virtual void OnImGuiRender() override {}

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
	virtual void OnUpdate() override;
};
