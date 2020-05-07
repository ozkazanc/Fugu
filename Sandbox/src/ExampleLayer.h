#pragma once
#include "Fugu.h"

class ExampleLayer : public Fugu::Layer {
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate() override;
	virtual void OnImGuiRender() override;
	void OnEvent(Fugu::Event & e) override;
};