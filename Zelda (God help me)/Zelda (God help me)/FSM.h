#pragma once

#include <vector>
#include <string>

class State {

protected:
	std::string m_id;
	std::string m_nextState;

public:
	State() : m_id(""), m_nextState("") {};
	virtual ~State() {};
	virtual void enter() {};
	virtual bool update() = 0;
	virtual void exit() {};
	std::string next_state() { return m_nextState; };
	std::string get_id() { return m_id; };
};

class FSM {

	std::vector<State*> m_states;
	State* m_currentState;

	void SwitchState(std::string p_state);

public:
	FSM();
	~FSM();
	void update();
	void add_state(State* p_state);
	void remove_state(State* p_state);
	void set_state(std::string p_id);
};