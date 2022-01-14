#include "dkpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGlRendererAPI.h"

namespace DK {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}