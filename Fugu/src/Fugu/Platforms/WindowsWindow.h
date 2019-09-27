#pragma once

#include "Fugu/Window.h"
#include <GLFW/glfw3.h>

namespace Fugu {

	class WindowsWindow : public Window {
	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;
			unsigned int Width;
			unsigned int Height;

			bool Vsync;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		void SetVsync(bool enable) override;
		bool IsVsync() const override;
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

	};

}
