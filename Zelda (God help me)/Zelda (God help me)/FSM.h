/*

FINITE STATE MACHINE

The Finite State Machine is used to create and store different game states (for example the main menu, options, the game itself etc).
Each state has an ID, and contains the ID of the next state that the game should load after the current one.

The purpouse of this system is to easely switch between different parts of the game itself,
without having to worry about what to change in the update functions as only the only updates that are run are the ones of the currently loaded state.

*/

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