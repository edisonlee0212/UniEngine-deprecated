#include "pch.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "RenderTarget.h"
#include "Default.h"
using namespace UniEngine;

void WindowManager::ResizeCallback(GLFWwindow* window, int width, int height) {
	GetInstance().m_windowWidth = width;
	GetInstance().m_windowHeight = height;
}

void UniEngine::WindowManager::SetMonitorCallback(GLFWmonitor* monitor, int event)
{
	if (event == GLFW_CONNECTED)
	{
		// The monitor was connected
		for (auto i : GetInstance().m_monitors) if (i == monitor) return;
		GetInstance().m_monitors.push_back(monitor);
	}
	else if (event == GLFW_DISCONNECTED)
	{
		// The monitor was disconnected
		for (auto i = 0; i < GetInstance().m_monitors.size(); i++) {
			if (monitor == GetInstance().m_monitors[i]) {
				GetInstance().m_monitors.erase(GetInstance().m_monitors.begin() + i);
			}
		}
	}
	GetInstance().m_primaryMonitor = glfwGetPrimaryMonitor();
}

void WindowManager::LateUpdate()
{
}

void UniEngine::WindowManager::Init(std::string name, bool fullScreen)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
	int size;
	auto monitors = glfwGetMonitors(&size);
	for (auto i = 0; i < size; i++) {
		GetInstance().m_monitors.push_back(monitors[i]);
	}
	GetInstance().m_primaryMonitor = glfwGetPrimaryMonitor();
	glfwSetMonitorCallback(SetMonitorCallback);

	
	// glfw window creation
	// --------------------
	const GLFWvidmode* mode = glfwGetVideoMode(GetInstance().m_primaryMonitor);
	GetInstance().m_windowWidth = fullScreen ? mode->width : mode->width - 200;
	GetInstance().m_windowHeight = fullScreen ? mode->height : mode->height - 200;

	GetInstance().m_window = glfwCreateWindow(GetInstance().m_windowWidth, GetInstance().m_windowHeight, name.c_str(), fullScreen ? GetInstance().m_primaryMonitor : nullptr, NULL);
	if(!fullScreen) glfwMaximizeWindow(GetInstance().m_window);
	glfwSetFramebufferSizeCallback(GetInstance().m_window, ResizeCallback);
	if (GetInstance().m_window == NULL)
	{
		Debug::Error("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(GetInstance().m_window);
}

GLFWwindow* UniEngine::WindowManager::GetWindow()
{
	return GetInstance().m_window;
}

GLFWmonitor* UniEngine::WindowManager::PrimaryMonitor()
{
	return GetInstance().m_primaryMonitor;
}

void UniEngine::WindowManager::PreUpdate()
{
	RenderTarget::BindDefault();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void UniEngine::WindowManager::Swap()
{
 	glfwSwapBuffers(GetInstance().m_window);
}

void UniEngine::WindowManager::DrawTexture(GLTexture2D* texture)
{
	RenderTarget::BindDefault();
	/* Make the window's context current */
	glViewport(0, 0, GetInstance().m_windowWidth, GetInstance().m_windowHeight);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	/* Render here */
	glDisable(GL_DEPTH_TEST);
	glDrawBuffer(GL_BACK);
	auto program = Default::GLPrograms::ScreenProgram;
	program->Bind();
	program->SetFloat("depth", 0);
	Default::GLPrograms::ScreenVAO->Bind();
	//Default::Textures::UV->Texture()->Bind(GL_TEXTURE_2D);
	texture->Bind(0);
	program->SetInt("screenTexture", 0);
	program->SetFloat2("center", glm::vec2(0));
	program->SetFloat2("size", glm::vec2(1.0));
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


