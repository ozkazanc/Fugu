#pragma once

#include "Fugu/Layer.h"

namespace Fugu {

	class FUGU_API ImGuiLayer : public Layer {

	private:
		float m_Time = 0.0f;

	public:
		ImGuiLayer();
		~ImGuiLayer();


		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& e) override;

	};
}
