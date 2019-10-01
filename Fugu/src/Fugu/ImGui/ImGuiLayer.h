#pragma once

#include "Fugu/Layer.h"
#include "Fugu/Events/Event.h"
#include "Fugu/Events/ApplicationEvent.h"
#include "Fugu/Events/KeyEvent.h"
#include "Fugu/Events/MouseEvent.h"

namespace Fugu {

	class FUGU_API ImGuiLayer : public Layer {

	private:
		float m_Time = 0.0f;

	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	};
}
