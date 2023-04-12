#ifndef BOOK_PAUSESTATE_H
#define BOOK_PAUSESTATE_H

#include "State.h"
#include "../../Common/d3dApp.h"
#include "../../Common/d3dApp.h"
#include "SpriteNode.h"
#include "SceneNode.hpp"

///This class is the derived class from state, which is used to stop gameplay
class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(const GameTimer& gt);
	virtual bool handleEvent();
	virtual void BuildScene();

private:
	SceneNode* pauseSceneGraph;
	SpriteNode* mPauseSprite;
};

#endif // BOOK_PAUSESTATE_HPP
