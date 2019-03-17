#pragma once

template< typename ContextType, typename StateIdType >
class GameState;

template< typename ContextType, typename StateIdType >
class GameStateMachine {

	public:
		using Context = ContextType;
		using StateId = StateIdType;
		using State = GameState<Context, StateId>;
		
	protected:
		Context context;
		StateId savedCurrentState;
		StateId currentState;
		StateId nextState;

	public:
		virtual ~GameStateMachine(void) = default;
		Context & getContext(void) { return this->context; }
		const Context & getContext(void) const { return this->context; }
    const StateId getCurrentState() { return this->currentState; }
    void changeState(StateId stateId, StateId nextId) { 
      this->currentState = stateId; 
      this->nextState = nextId; 
    }
		
};