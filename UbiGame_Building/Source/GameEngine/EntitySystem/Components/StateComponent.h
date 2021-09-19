#pragma once

#include "GameEngine/EntitySystem/Component.h"

namespace GameEngine
{
	template <class T>
	class StateComponent : public Component
	{
	public:
		StateComponent();
		virtual ~StateComponent();

		T GetState() { return m_state; }
		void SetState(T newState) { m_state = newState; }
	private:
		T m_state;
	};
}
