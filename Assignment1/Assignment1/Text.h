#pragma once
#include "Entity.h"
#include <string>

class Text : public Entity {

public:
	enum Menu
	{
		SplashText,
		MenuText1,
		MenuText2
	};

public:
	Text(Menu menu, Game* game);

private:
	void updateCurrent(const GameTimer& gt);
	void check(const GameTimer& gt);
	virtual void drawCurrent() const;
	virtual void buildCurrent();

private:
	Menu mMenu;
	std::string	mSprite;
	bool flash;
	bool show;
};
