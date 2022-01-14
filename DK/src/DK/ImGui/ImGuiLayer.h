#pragma once

#include "DK/Layer.h"

#include "DK/Events/ApplicationEvent.h"
#include "DK/Events/KeyEvent.h"
#include "DK/Events/MouseEvent.h"

namespace DK {

	class DK_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}