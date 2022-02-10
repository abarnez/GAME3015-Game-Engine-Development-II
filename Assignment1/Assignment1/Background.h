/**
 * @file Background.h
 * @author Alexander Barnes
 * @date 2/9/2022
 * @brief
 * The background is based on the SpriteNode from the week3demo7 and is used primairly for our background sprite.
 * Build current builds the render item and sets up the geomerty.
 * Draw current gets our transform in the world and counts dirty frames
 * Update current can be used to update it with things like movement 
 */
#pragma once
#include "Entity.h"

class bckGround : public Entity
{
public:
	bckGround(Game* game);

private:
	virtual void updateCurrent(const GameTimer& gt);
	virtual void drawCurrent() const;
	virtual void buildCurrent();
};