#pragma once
#include "SceneNode.hpp"

class Entity :
    public SceneNode
{
public:
	Entity(Game* mGame);
	void				setVelocity(XMFLOAT3 velocity);
	void				setVelocity(float vx, float vy);
	XMFLOAT3			getVelocity() const;

	virtual	void		updateCurrent(const GameTimer& gt);

public:
	XMFLOAT3		mVelocity;
};

