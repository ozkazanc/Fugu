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

		bool OnWindowResizeEvent(WindowResizeEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);

	public:
		ImGuiLayer();
		~ImGuiLayer();


		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& e) override;

	};
}
