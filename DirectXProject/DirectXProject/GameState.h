#ifndef BOOK_GAMESTATE_H
#define BOOK_GAMESTATE_H

#include "State.h"
#include "World.hpp"
#include "Player.h"
#include "../../Common/d3dApp.h"

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")

///This class is the derived class from state, which to hold the game world
class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(const GameTimer& gt);
	virtual bool handleEvent();
	virtual void BuildScene();

private:
	World* mWorld;
	Player& mPlayer;

	SceneNode* pauseSceneGraph;
	SpriteNode* mPauseSprite;

	SpriteNode* mGround;
	SpriteNode* mSky;
	Aircraft* mplayerAircraftOne;
	Aircraft* mplayerAircraftTwo;
};

#endif // BOOK_GAMESTATE_HPP