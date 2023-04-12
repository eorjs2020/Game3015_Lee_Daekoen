#ifndef BOOK_TITLESTATE_H
#define BOOK_TITLESTATE_H

#include "State.h"
#include "../../Common/d3dApp.h"
#include "SpriteNode.h"
#include "SceneNode.hpp"

///This class is the derived class from state, which is used as get keyboard input check
class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(const GameTimer& gt);
	virtual bool handleEvent();
	virtual void BuildScene();

private:
	SceneNode* sceneGraph;
	SpriteNode* mBackgroundSprite;
};

#endif // BOOK_TITLESTATE_HPP
