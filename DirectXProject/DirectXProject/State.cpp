#include "State.h"
#include "StateStack.h"

/// The defualt conconstructor for context
/// 
/// @param: Player&
/// @param: Game 
State::Context::Context(Player& player, Game* game)
	: player(&player)
	, mGame(game)
{

}
/// The defualt conconstructor for state
/// 
/// @param: StateStake&
/// @param: Context
State::State(StateStack& stack, Context context)
	: mStack(&stack)
	, mContext(context)
{
	mGame = context.mGame;
}

/// The destructor class
State::~State()
{
}

/// The function use to request a push on to stack
/// 
/// @param: States::ID
void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

/// The function use to request a pop on to stack
/// 
/// @param: States::ID
void State::requestStackPop()
{
	mStack->popState();
}

/// The function use to request a clear the stack
/// 
/// @param: States::ID
void State::requestStateClear()
{
	mStack->clearStates();
}

/// The get context
/// 
/// @param: Context
State::Context State::getContext() const
{
	return mContext;
}
