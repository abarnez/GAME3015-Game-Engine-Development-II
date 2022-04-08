/**
 * @file World.h
 * @author Alexander Barnes
 * @date 2/9/2022
 * @brief
 * The world acts like a unity scene the way I understand it, based on the sfml version in week3-demo7 I based the structure on that as closely as possible.
 * We have our game world which takes place in the window, our update (similar to unity update or ue4 tick), draw gets called on the scene node to draw current and children
 * Build Scene creates our scene and instantiates our player, escorts, and the background. Similar to how we used the build render items in other projects.
 * We have a layer enumerator to differentiate the different layers.
 */
#pragma once
#include "SceneNode.h"
#include "Aircraft.h"
#include "Background.h"
#include "CommandQueue.h"
#include "Command.h"
#include "SplashScreen.h"

class World
{
public:
	explicit World(Game* window);
	void update(const GameTimer& gt);
	void draw();
	void buildScene();
	CommandQueue& getCommandQueue();
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
	CommandQueue mCommandQueue;
	std::array<SceneNode*, LayerCount>	mSceneLayers;

	XMFLOAT4 mWorldBounds;
	XMFLOAT2 mSpawnPosition;

	float mMoveSpeed;
	
	bckGround* mBackground;
	bckGround* mBackground2;

	Aircraft* mPlayerAircraft;
	Aircraft* escort1;
	Aircraft* escort2;

	SplashScreen* mSplashScreen;
};

