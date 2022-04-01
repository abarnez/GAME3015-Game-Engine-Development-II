#include "Entity.h"

Entity::Entity(Game* game) : SceneNode(game), mVelocity(0, 0, 0)
{
}

void Entity::setVelocity(XMFLOAT3 velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy, float vz)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
	mVelocity.z = vz;
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
	move(mV.x, mV.y, mV.z);
}

void Entity::updateChildren(const GameTimer & gt)
{
	for (Ptr& child : mChildren)
	{
		XMFLOAT2 mV;
		mV.x = mVelocity.x * gt.DeltaTime();
		mV.y = mVelocity.y * gt.DeltaTime();
		child->move(mV.x, mV.y, 0);
	}
}


void Entity::accelerate(XMFLOAT3 velocity)
{
	mVelocity.x += velocity.x; //not sure whats going on here
	mVelocity.y += velocity.y; //not sure whats going on here
	mVelocity.z += velocity.z; //not sure whats going on here
}

void Entity::accelerate(float vx, float vy, float vz)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
	mVelocity.z += vz;
}