#include "pch.h"
#include "InputManager.h"
#include "UniEngine.h"
#include "EditorManager.h"
#include "imgui_internal.h"
#include "WindowManager.h"
using namespace UniEngine;

inline void InputManager::Init() {
}

inline bool InputManager::GetKey(int key) {
	bool retVal = false;
	ImGui::Begin("Camera");
	{
		// Using a Child allow to fill all the space of the window.
		// It also allows customization
		if (ImGui::BeginChild("CameraRenderer")) {
			if (ImGui::IsWindowFocused())
			{
				const auto state = glfwGetKey(WindowManager::GetWindow(), key);
				retVal = state == GLFW_PRESS || state == GLFW_REPEAT;
			}
		}
		ImGui::EndChild();
	}
	ImGui::End();
	return retVal;
}

inline bool InputManager::GetMouse(int button) {
	bool retVal = false;
	ImGui::Begin("Camera");
	{
		// Using a Child allow to fill all the space of the window.
		// It also allows customization
		if (ImGui::BeginChild("CameraRenderer")) {
			if (ImGui::IsWindowFocused())
			{
				retVal = glfwGetMouseButton(WindowManager::GetWindow(), button) == GLFW_PRESS;
			}
		}
		ImGui::EndChild();
	}
	ImGui::End();
	return retVal;
}
inline glm::vec2 InputManager::GetMouseAbsolutePosition() {
	double x = FLT_MIN;
	double y = FLT_MIN;
	ImGui::Begin("Camera");
	{
		// Using a Child allow to fill all the space of the window.
		// It also allows customization
		if (ImGui::BeginChild("CameraRenderer")) {
			if (ImGui::IsWindowFocused())
			{
				glfwGetCursorPos(WindowManager::GetWindow(), &x, &y);
			}
		}
		ImGui::EndChild();
	}
	ImGui::End();
	return glm::vec2(x, y);
}

inline bool InputManager::GetMousePositionInternal(ImGuiWindow* window, glm::vec2& pos)
{
	ImGuiIO& io = ImGui::GetIO();
	const auto viewPortSize = window->Size;
	const auto overlayPos = window->Pos;
	const ImVec2 windowPos = ImVec2(overlayPos.x + viewPortSize.x, overlayPos.y);
	if (ImGui::IsMousePosValid()) {
		pos.x = io.MousePos.x - windowPos.x;
		pos.y = io.MousePos.y - windowPos.y;
		return true;
	}
	return false;
}

bool InputManager::GetMousePosition(glm::vec2& pos)
{
	bool retVal = false;
	ImGui::Begin("Camera");
	{
		if (ImGui::BeginChild("CameraRenderer")) {
			if (ImGui::IsWindowFocused())
			{
				retVal = GetMousePositionInternal(ImGui::GetCurrentWindowRead(), pos);
			}
		}
		ImGui::EndChild();
	}
	ImGui::End();
	return retVal;
}

void InputManager::LateUpdate()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("View"))
		{
			ImGui::Checkbox("Input Manager", &GetInstance().m_enableInputMenu);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	if (GetInstance().m_enableInputMenu)
	{
		ImGui::Begin("Input Manager");
		ImGui::End();
	}
}

bool InputManager::GetKeyInternal(int key, GLFWwindow* window)
{
	auto state = glfwGetKey(window, key);
	return state == GLFW_PRESS;
}

bool InputManager::GetMouseInternal(int button, GLFWwindow* window)
{
	return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

glm::vec2 InputManager::GetMouseAbsolutePositionInternal(GLFWwindow* window)
{
	double x = FLT_MIN;
	double y = FLT_MIN;
	glfwGetCursorPos(window, &x, &y);
	return glm::vec2(x, y);
}

