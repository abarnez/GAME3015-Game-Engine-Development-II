/**
 * @file Aircraft.h
 * @author Abdulhakeem Idris
 * @date 2/9/2022
 * @brief
 * This script is derived from the Entity class. It overrides the updateCurrent(), drawCurrent(), and buildCurrent()
 * to implement custom appearance and behaviour from a generic entity instance.\n
 * For this custom behaviour, the updateCurrent() moves the plane from side to side on the screen.
 */
#pragma once
#include "Entity.h"
#include <string>

class Aircraft : public Entity
{
public:
	enum Type
	{
		Eagle,
		Raptor,
	};


public:
	Aircraft(Type type, Game* game);
	virtual unsigned int getCategory() const;
		/*
	{
		switch (mType)
		{
		case Eagle:
			return Category::PlayerAircraft;
		default:
			return Category::EnemyAircraft;
		}
	}
	*/
	
	
private:
	void updateCurrent(const GameTimer& gt);
	virtual void drawCurrent() const;
	virtual void buildCurrent();

private:
	Type mType;
	std::string	mSprite;
};
