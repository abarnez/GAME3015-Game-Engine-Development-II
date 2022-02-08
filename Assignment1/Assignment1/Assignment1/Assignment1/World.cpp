#include "World.h"

World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mBackground2(nullptr)
	, mWorldBounds(0.f, 0.f, 600.f, 2000.f)
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(-0.f)
{
}

void World::update(const GameTimer& gt)
{
	//XMFLOAT3 pos = raptor->getWorldPosition();
	//XMFLOAT2 vel = raptor->getVelocity();
	////vel.x = 5.0f;
	//if ( pos.x >= 6 ||pos.x <= -6) {
	//	vel.x = -vel.x;
	//
	//}
	//raptor->setVelocity(vel);
	XMFLOAT3 pos1 = mBackground->getWorldPosition();
	XMFLOAT3 pos2 = mBackground2->getWorldPosition();
	if (pos1.z < -17.5) {
		mBackground->setPosition(0, 0, 18.5);

	}
	if (pos2.z < -17.5) {
		mBackground2->setPosition(0, 0, 18.5);

	}
	mSceneGraph->update(gt);

}

void World::draw()
{
	mSceneGraph->draw();
}



void World::buildScene()
{
	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mGame));
	mPlayerAircraft = (Aircraft*)player.get();
	mPlayerAircraft->setPosition(0, 2.5, 0);
	mPlayerAircraft->setScale(0.1, 0.1, 0.1);
	mPlayerAircraft->setVelocity(5, mScrollSpeed, 0);
	mSceneGraph->attachChild(std::move(player));
	
	

	std::unique_ptr<Aircraft> enemy(new Aircraft(Aircraft::Raptor, mGame));
	raptor = (Aircraft*)enemy.get();
	raptor->setPosition(2, 2, -1);
	raptor->setScale(0.1, 0.1, 0.1);
	raptor->setVelocity(5, mScrollSpeed, 0);
	mPlayerAircraft->attachChild(std::move(enemy));
	


	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	raptor2 = (Aircraft*)enemy2.get();
	raptor2->setPosition(-2, 2, -1);
	raptor2->setScale(0.1, 0.1, 0.1);
	raptor2->setVelocity(5, mScrollSpeed, 0);
	mPlayerAircraft->attachChild(std::move(enemy2));

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	mBackground = (SpriteNode*)backgroundSprite.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 2.0);
	mBackground->setScale(1.0, 1.0, 1);
	mBackground->setVelocity(0.0, 0.0, -1.0);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<SpriteNode> backgroundSprite2(new SpriteNode(mGame));
	mBackground2 = (SpriteNode*)backgroundSprite2.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground2->setPosition(0, 0, 18);
	mBackground2->setScale(1.0, 1.0, 1);
	mBackground2->setVelocity(0.0, 0.0, -1.0);
	mSceneGraph->attachChild(std::move(backgroundSprite2));

	mSceneGraph->build();
}