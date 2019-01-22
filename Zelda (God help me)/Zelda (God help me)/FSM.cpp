#include "FSM.h"

void FSM::SwitchState(std::string p_state)
{
	for (State* state : m_states) {
		if (state->get_id() == p_state) {
			if (m_currentState != nullptr)
				m_currentState->exit();
			m_currentState = state;
			m_currentState->enter();
			return;
		}
	}
}

FSM::FSM()
{
}

FSM::~FSM()
{
}

void FSM::update()
{
	if (m_currentState == nullptr)
		return;

	if (m_currentState->update() == false) {
		SwitchState(m_currentState->next_state());
	}
}

void FSM::add_state(State * p_state)
{
	if (p_state != nullptr)
		m_states.push_back(p_state);
	else
		return;
}

void FSM::remove_state(State * p_state)
{
	if (p_state == nullptr)
		return;

	for (int i = 0; i < m_states.size(); i++) {

		if (m_states[i] == p_state) {
			m_states.erase(m_states.begin() + i);

			if (m_currentState != nullptr) {

				if (m_currentState = m_states[i]) {
					m_currentState->exit();
					m_currentState = nullptr;
				}
			}
		}
	}
}

void FSM::set_state(std::string p_id)
{
	for (State* state : m_states) {
		if (state->get_id() == p_id) {

			if (m_currentState != nullptr) {
				m_currentState->exit();
			}
			m_currentState = state;
			m_currentState->enter();
		}
	}
}
