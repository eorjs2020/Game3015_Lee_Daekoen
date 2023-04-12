#include "World.hpp"

World::World(Game* mGame, Player* player)
	: mSceneGraph(new SceneNode(mGame))
	, mGame(mGame)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f) //Left, Right, Down, Up
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(5.0f)
	, mPlayer(player)
{	

}

void World::update(const GameTimer& gt)
{
	mPlayerAircraft->setVelocity(0, 0);
	while (!mCommandQueue.isEmpty())
		mSceneGraph->onCommand(mCommandQueue.pop(), gt);	
	mSceneGraph->update(gt);
}

void World::draw()
{
	mSceneGraph->draw();
}

void World::buildScene()
{
	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mGame));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(0, 2.5, 2.7);
	mPlayerAircraft->setWorldRotation(-0.1f, 0, 0);
	mPlayerAircraft->setScale(4.5, 4.5, 4.5);
	
	mSceneGraph->attachChild(std::move(player));


	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	mBackground = backgroundSprite.get();	
	mBackground->setPosition(0, 0, 0.0);
	mBackground->setScale(50.0, 1.0, 900.0);
	mBackground->buildSprite("Desert", "boxGeo");
	mBackground->setVelocity(XMFLOAT3(0, 0, -mScrollSpeed * 2));
	mSceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<SpriteNode> backgroundSprite2(new SpriteNode(mGame));
	mBackground = backgroundSprite2.get();
	mBackground->setPosition(-25, 0, 0.0);
	mBackground->setScale(100.0, 1.0, 900.0);
	mBackground->setWorldRotation(0, 0, -1);
	mBackground->buildSprite("Desert", "boxGeo");
	mBackground->setVelocity(XMFLOAT3(0, 0, -mScrollSpeed * 2));
	mSceneGraph->attachChild(std::move(backgroundSprite2));

	std::unique_ptr<SpriteNode> backgroundSprite3(new SpriteNode(mGame));
	mBackground = backgroundSprite3.get();
	mBackground->setPosition(25, 0, 0.0);
	mBackground->setScale(100.0, 1.0, 900.0);
	mBackground->setWorldRotation(0, 0, 1);
	mBackground->buildSprite("Desert", "boxGeo");
	mBackground->setVelocity(XMFLOAT3(0, 0, -mScrollSpeed * 2));
	mSceneGraph->attachChild(std::move(backgroundSprite3));

	mSceneGraph->build();
}
