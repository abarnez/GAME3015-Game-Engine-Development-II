/**
 * @file Entity.h
 * @author Abdulhakeem Idris
 * @date 2/9/2022
 * @brief
 * This script is derived from the SceneNode class. It overrides the updateCurrent() and updateChildren() 
 * to implement a generic Entity behaviour.\n
 * The entity has a velocity variable to hold the velocity of any entity instance, as well as setter/getter 
 * functions for changing the entity object's velocity.
 */
#pragma once
#include "SceneNode.h"

class Entity : public SceneNode
	
{
public:
	Entity(Game* game);
	void setVelocity(XMFLOAT3 velocity);
	void setVelocity(float vx, float vy, float vz);
	XMFLOAT3 getVelocity() const;

	virtual	void updateCurrent(const GameTimer& gt);
	virtual	void updateChildren(const GameTimer& gt);

public:
	XMFLOAT3 mVelocity;
};


