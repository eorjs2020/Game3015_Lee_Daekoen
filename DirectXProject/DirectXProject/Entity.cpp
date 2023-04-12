#include "Entity.hpp"

Entity::Entity(Game* mGame) : SceneNode(mGame), mVelocity(0, 0, 0)
{
}

void Entity::setVelocity(XMFLOAT3 velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

XMFLOAT3 Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::updateCurrent(const GameTimer& gt) 
{
	XMFLOAT3 mV;
	
	mV.x = mVelocity.x * gt.DeltaTime();
	mV.y = mVelocity.y * gt.DeltaTime();
	mV.z = mVelocity.z * gt.DeltaTime();
	if (mV.x + mWorldPosition.x > 3 || mV.x + mWorldPosition.x < -3)
	{
		mV.x = 0;
	}
	if (mV.y + mWorldPosition.y > 5.5 || mV.y + mWorldPosition.y < 1.5)
	{
		mV.y = 0;
	}
	move(mV.x, mV.y, mV.z);

	renderer->World = getWorldTransform();
	renderer->NumFramesDirty++;
}
