#pragma once

#include <string>

namespace DK
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSrc, std::string& fragmentSrc);
	private:
		uint32_t m_RendererID;
	};
}
