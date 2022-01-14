#include "dkpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace DK {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		DK_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		DK_CORE_ASSERT(status, "Failed to initialize Glad!");

		DK_CORE_INFO("OpenGL Info:");
		DK_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		DK_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		DK_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}