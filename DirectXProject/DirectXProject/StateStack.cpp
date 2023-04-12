#include "StateStack.h"

#include <cassert>

/// The defualt conconstructor
/// 
/// @param: Context 
StateStack::StateStack(State::Context context)
	: mStack()
	, mPendingList()
	, mContext(context)
	, mFactories()
{
}

/// Used to call update function from states in stack
///
/// @param: const GameTimer&
void StateStack::update(const GameTimer& gt)
{
	// Iterate from top to bottom, stop as soon as update() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(gt))
			break;
	}

	applyPendingChanges();
}

/// Used to call draw function from states in stack
void StateStack::draw()
{
	// Draw all active states from bottom to top
	for (State::Ptr& state : mStack)
		state->draw();
}

///Used to call all handle events function from states in stack
void StateStack::handleEvent()
{
	// Iterate from top to bottom, stop as soon as handleEvent() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent())
			break;
	}

	applyPendingChanges();
}

/// Push a state on top of the stack
/// 
/// @param: States::ID: which state
void StateStack::pushState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Push, stateID));
}

/// Pop a state on top of the stack
/// 
/// @param: States::ID: which state
void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Pop));
}

/// Clear all states in the stack
void StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(Clear));
}

/// Check if stack has any states
/// 
/// @returns: bool
bool StateStack::isEmpty() const
{
	return mStack.empty();
}

/// Create a State 
/// 
/// @param: States::ID: which state
/// @returns: Ptr StateStack
State::Ptr StateStack::createState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}


/// Add changes to the stack
void StateStack::applyPendingChanges()
{
	for (PendingChange change : mPendingList)
	{
		switch (change.action)
		{
		case Push:
			mStack.push_back(createState(change.stateID));
			break;

		case Pop:
			mStack.pop_back();
			break;

		case Clear:
			mStack.clear();
			break;
		}
	}

	mPendingList.clear();
}

/// The defualt conconstructor
/// 
/// @param: Action
/// @param: States::ID: which state
StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
	: action(action)
	, stateID(stateID)
{
}
