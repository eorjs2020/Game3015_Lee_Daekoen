#pragma once
#include "Entity.hpp"

class SpriteNode :
    public Entity
{
public:
	SpriteNode(Game* mGame);

private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();
};
