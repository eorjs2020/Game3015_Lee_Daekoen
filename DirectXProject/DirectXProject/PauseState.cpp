#include "PauseState.h"
#include "Game.hpp"

/// The defualt conconstructor
/// 
/// @param: StateStack&
/// @param: Context 
PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context),
	pauseSceneGraph(new SceneNode(mGame))
{
	BuildScene();
}

/// Used draw state's game objects
void PauseState::draw()
{
	pauseSceneGraph->draw();
}

/// Used to keep game paused
/// 
/// @param: const GameTimer&
bool PauseState::update(const GameTimer& gt)
{
	pauseSceneGraph->update(gt);
	return false;
}

///Handle any commands once or real time input
bool PauseState::handleEvent()
{
	//Unpuase game
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		requestStackPop();
		mGame->gamePaused = false;
	}

	return true;
}

///Build game objects for scene (Not used)
void PauseState::BuildScene()
{

}


