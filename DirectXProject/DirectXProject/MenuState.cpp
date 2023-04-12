#include "MenuState.h"
#include "Game.hpp"

/// The defualt conconstructor
/// 
/// @param: StateStack&
/// @param: Context 
MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context),
	sceneGraph(new SceneNode(mGame))
{

	std::wstring title = L"Menu";
	mGame->ChangCaption(title);
	BuildScene();
}

/// Used draw state's game objects
void MenuState::draw()
{
	sceneGraph->draw();
}

/// Used to keep game paused
/// 
/// @param: const GameTimer&
bool MenuState::update(const GameTimer& gt)
{	
	sceneGraph->update(gt);
	return true;
}

///Handle any commands once or real time input
bool MenuState::handleEvent()
{
	//Game Scene
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		requestStackPop();
		mGame->FlushCommandList();
		if (!isOnExit)
		{
			requestStackPush(States::Game);
		}
		else
		{
			requestStackPop();
		}
		
	}	

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		isOnExit = false;
		if (isOnExit)
		{
			mBackgroundSprite->setPosition(-1.1, -0.5, -1);
		}
		else
		{
			mBackgroundSprite->setPosition(-1.1, 0.2, -1);
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		isOnExit = true;
		if (isOnExit)
		{
			mBackgroundSprite->setPosition(-1.1, -0.5, -1);
		}
		else
		{
			mBackgroundSprite->setPosition(-1.1, 0.2, -1);
		}
	}
	return true;
}

///Build game objects for scene (Not used)
void MenuState::BuildScene()
{
	
	mGame->mAllRitems.clear();
	mGame->mFrameResources.clear();
	mGame->mRitemLayer[(int)RenderLayer::AlphaTested].clear();

	mGame->mCamera.SetPosition(0, 0, -8);
	
	mGame->BuildMaterials();

	std::unique_ptr<SpriteNode> Menu(new SpriteNode(mGame));
	mBackgroundSprite = Menu.get();	
	mBackgroundSprite->setPosition(0, 0, 0);
	mBackgroundSprite->setWorldRotation(-1.57f, 0, 0);
	mBackgroundSprite->setScale(6.6f, 4.5f, 6.5f);
	
	sceneGraph->attachChild(std::move(Menu));
	mBackgroundSprite->buildSprite("Menu", "boxGeo");


	std::unique_ptr<SpriteNode> Selector(new SpriteNode(mGame));
	mBackgroundSprite = Selector.get();
	mBackgroundSprite->setPosition(-1.1, 0.2, -1);
	//mBackgroundSprite->setPosition(-1.1, -0.5, -1);
	mBackgroundSprite->setWorldRotation(-1.57f,0, -90 * XM_PI / 180);
	mBackgroundSprite->setScale(0.5f, 0.5f, 0.5f);

	sceneGraph->attachChild(std::move(Selector));
	mBackgroundSprite->buildSprite("Eagle", "boxGeo");

	mGame->BuildFrameResources();

	
}
