#include "fgpch.h"
#include "WindowsInput.h"

#include "Fugu/Application.h"
#include "GLFW/glfw3.h"

namespace Fugu {

	Input* Input::s_Instance = new WindowsInput();
	
	bool WindowsInput::IsKeyPressedImpl(int keycode) const
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) const
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl() const
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return {(float)xpos, (float)ypos};
	}

	float WindowsInput::GetMouseXImpl() const
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl() const
	{
		auto p = GetMousePositionImpl();
		return p.second;
	}
}