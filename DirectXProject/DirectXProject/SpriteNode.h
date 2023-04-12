#pragma once
#include "Entity.hpp"

class SpriteNode :
    public Entity
{
public:
	SpriteNode(Game* mGame);
	void buildSprite(std::string MatName, std::string GeoName);
	void buildSpriteOpaque(std::string MatName, std::string GeoName);
private:
	virtual void		drawCurrent() const;
};
