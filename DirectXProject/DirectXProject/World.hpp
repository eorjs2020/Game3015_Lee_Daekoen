#pragma once
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "SpriteNode.h"
#include "Player.h"
#include "CommandQueue.h"
#include "Command.h"


using namespace std;
class Game;
class World 
{
public:
	World(Game* window, Player* player);
	void								update(const GameTimer& gt);
	void								draw();

	//void								loadTextures();
	void								buildScene();
	std::unordered_map<std::string, std::wstring>* getTextures() { return &mTexture; };
	CommandQueue& getCommandQueue() { return mCommandQueue; };

private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};


private:
	Game*								mGame;
	Player*								mPlayer;
	SceneNode*							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;

	XMFLOAT4							mWorldBounds;
	XMFLOAT2		    				mSpawnPosition;
	float								mScrollSpeed;
	Aircraft*							mPlayerAircraft;
	SpriteNode*							mBackground;
	Aircraft*							mEnemy;
	std::unordered_map<std::string, std::wstring> mTexture;
	CommandQueue mCommandQueue;
};
