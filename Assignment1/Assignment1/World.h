#pragma once
#include "SceneNode.h"
#include "Aircraft.h"
#include "Background.h"

class World
{
public:
	explicit							World(Game* window);
	void								update(const GameTimer& gt);
	void								draw();

	//void								loadTextures();
	void								buildScene();


private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};


private:
	Game* mGame;

	SceneNode* mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;

	XMFLOAT4							mWorldBounds;
	XMFLOAT2		    				mSpawnPosition;
	float								mScrollSpeed;
	Aircraft* mPlayerAircraft;
	bckGround* mBackground;
	bckGround* mBackground2;
	Aircraft* raptor;
	Aircraft* raptor2;
};

