#include "GameState.h"
#include "Game.hpp"

/// The defualt conconstructor
/// 
/// @param: StateStack&
/// @param: Context 
GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(&(mGame->mWorld))
	, mPlayer(*context.player),
	mPauseSprite(nullptr),
	pauseSceneGraph(new SceneNode(mGame))
{
	BuildScene();
}

/// Used draw state's game objects
void GameState::draw()
{
	mWorld->draw();
}

/// Used to keep game paused
/// 
/// @param: const GameTimer&
bool GameState::update(const GameTimer& gt)
{
	mWorld->update(gt);

	CommandQueue& commands = mWorld->getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	return true;
}

///Handle any commands once or real time input
bool GameState::handleEvent()
{
	// Game input handling
	CommandQueue& commands = mWorld->getCommandQueue();
	mPlayer.handleEvent(commands, 46);
	mPlayer.handleRealtimeInput(commands);

	//Pause the game
#pragma region
	if (GetAsyncKeyState('P') & 0x8000)
	{
		requestStackPush(States::Pause);
		mGame->gamePaused = true;
	}
#pragma endregion
	return true;
}

///Build game objects for game state and pause state
void GameState::BuildScene()
{
	mGame->mAllRitems.clear();
	mGame->mFrameResources.clear();
	mGame->mRitemLayer[(int)RenderLayer::AlphaTested].clear();

	mGame->mTexture.clear();
	//mGame->loadTextures();
	mGame->mCamera.SetPosition(0, 6, -10);
	mGame->BuildMaterials();


	mWorld->buildScene();

	std::unique_ptr<SpriteNode> BGSky(new SpriteNode(mGame));
	mPauseSprite = BGSky.get();
	mPauseSprite->setPosition(0.0f, 6.0f, -2);
	mPauseSprite->setWorldRotation(-1.57f, 0, 0);
	mPauseSprite->setScale(4, 4, 4);
	pauseSceneGraph->attachChild(std::move(BGSky));
	mPauseSprite->buildSpriteOpaque("Raptor", "boxGeo");


	mGame->BuildFrameResources();

}

