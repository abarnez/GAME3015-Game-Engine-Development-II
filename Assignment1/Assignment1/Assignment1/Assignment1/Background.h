#pragma once
#include "Entity.h"

class bckGround :
	public Entity
{
public:
	bckGround(Game* game);

private:
	virtual void		updateCurrent(GameTimer& gt);
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();
};