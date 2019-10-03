#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Fugu/ImGui/ImGuiLayer.h"

#include "Fugu/Renderer/Buffer.h"
#include "Fugu/Renderer/Shader.h"

namespace Fugu {

	class FUGU_API Application {
	private:
		static Application* s_Instance;

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		unsigned int m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		bool OnWindowClose(WindowCloseEvent& e);

	public:
		Application();
		virtual ~Application();

		inline static Application& Application::GetInstance() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		void Run();
		
		virtual void OnEvent(Event& e);
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	};


	// To be defined by Client
	Application* CreateApplication();

}
