#include <DK.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public DK::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(DK::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		DK::Ref<DK::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(DK::VertexBuffer::Create(vertices, sizeof(vertices)));
		DK::BufferLayout layout = {
			{ DK::ShaderDataType::Float3, "a_Position" },
			{ DK::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		DK::Ref<DK::IndexBuffer> indexbuffer;
		indexbuffer.reset(DK::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexbuffer);

		m_SquareVA.reset(DK::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		DK::Ref<DK::VertexBuffer> squareVB;
		squareVB.reset(DK::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ DK::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		DK::Ref<DK::IndexBuffer> squareIB;
		squareIB.reset(DK::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}

		)";

		m_Shader.reset(DK::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(DK::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
	}

	void OnUpdate(DK::Timestep ts) override
	{
		if (DK::Input::IsKeyPressed(DK_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		if (DK::Input::IsKeyPressed(DK_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		if (DK::Input::IsKeyPressed(DK_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		if (DK::Input::IsKeyPressed(DK_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		DK::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		DK::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		DK::Renderer::BeginScene(m_Camera);

		
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<DK::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<DK::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				DK::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		//DK::Renderer::Submit(m_Shader, m_VertexArray);

		DK::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Colour", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(DK::Event& event) override
	{
	}

private:
	DK::Ref<DK::Shader> m_Shader;
	DK::Ref<DK::VertexArray> m_VertexArray;

	DK::Ref<DK::Shader> m_FlatColorShader;
	DK::Ref<DK::VertexArray> m_SquareVA;

	DK::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.5f;

	float m_CameraRotation = 0.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public DK::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

DK::Application* DK::CreateApplication()
{
	return new Sandbox();
}