#include "TitleState.h"
#include "Game.hpp"

/// The defualt conconstructor
/// 
/// @param: StateStack&
/// @param: Context 
TitleState::TitleState(StateStack & stack, Context context)
	: State(stack, context),
	sceneGraph(new SceneNode(mGame))
{

	std::wstring title = L"Title";
	mGame->ChangCaption(title);
	BuildScene();
}

/// Used draw state's game objects
void TitleState::draw()
{
	sceneGraph->draw();
}

/// Used to keep game paused
/// 
/// @param: const GameTimer&
bool TitleState::update(const GameTimer& gt)
{
	sceneGraph->update(gt);

	return true;
}

///Handle any commands once or real time input
bool TitleState::handleEvent()
{
	
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		requestStackPop();
		mGame->FlushCommandList();
		requestStackPush(States::Menu);
	}
	return true;
}

///Build game objects for scene
void TitleState::BuildScene()
{
	mGame->mCamera.SetPosition(0, 0, -8);
	

	std::unique_ptr<SpriteNode> BGSky(new SpriteNode(mGame));
	mBackgroundSprite = BGSky.get();
	mBackgroundSprite->setPosition(0, 0, 0);
	mBackgroundSprite->setWorldRotation(-1.57f, 0, 0);	
	mBackgroundSprite->setScale(6.6f, 4.5f, 6.5f);
	sceneGraph->attachChild(std::move(BGSky));
	mBackgroundSprite->buildSprite("Title", "boxGeo");
	
	
	
	
	mGame->BuildFrameResources();
	
}
