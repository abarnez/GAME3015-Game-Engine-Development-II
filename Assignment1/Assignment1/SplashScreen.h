#pragma once
#include "Entity.h"

class SplashScreen : public Entity
{
public:
	SplashScreen(Game* game);

private:
	virtual void updateCurrent(const GameTimer& gt);
	virtual void drawCurrent() const;
	virtual void buildCurrent();
	void check(const GameTimer& gt);
};