#pragma once
#include "Entity.h"

class Menu : public Entity
{
public:
	Menu(Game* game);

private:
	virtual void updateCurrent(const GameTimer& gt);
	virtual void drawCurrent() const;
	virtual void buildCurrent();
	void check(const GameTimer& gt);
	bool show;
};
