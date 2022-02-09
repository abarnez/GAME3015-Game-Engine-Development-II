#pragma once
#include "Entity.h"
#include <string>

class Aircraft :
	public Entity
{
public:
	enum Type
	{
		Eagle,
		Raptor,
	};


public:
	Aircraft(Type type, Game* game);
	
	void Strafe(float d);

private:
	void				updateCurrent(const GameTimer& gt);
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();


private:
	Type				mType;
	std::string			mSprite;
};
