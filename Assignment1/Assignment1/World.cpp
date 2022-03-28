#include "World.h"

World::World(Game* game)	: mSceneGraph(new SceneNode(game))	, mGame(game)	, mPlayerAircraft(nullptr)	, mBackground(nullptr)	, mBackground2(nullptr)
	, mWorldBounds(0.f, 0.f, 600.f, 2000.f)	, mSpawnPosition(0.f, 0.f)	, mMoveSpeed(-0.f), mQueue(nullptr)
{
}




void World::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);

	// Forward commands to the scene graph
	while (!mQueue->isEmpty())
		mSceneGraph->onCommand(mQueue->pop(), gt);



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
	mPlayerAircraft->setVelocity(5, mMoveSpeed, 0);
	mSceneGraph->attachChild(std::move(player));
	
	std::unique_ptr<Aircraft> escortr(new Aircraft(Aircraft::Raptor, mGame));
	escort1 = (Aircraft*)escortr.get();
	escort1->setPosition(2, 2, -1);
	escort1->setScale(0.1, 0.1, 0.1);
	escort1->setVelocity(5, mMoveSpeed, 0);
	mPlayerAircraft->attachChild(std::move(escortr));
	
	std::unique_ptr<Aircraft> escortl(new Aircraft(Aircraft::Raptor, mGame));
	escort2 = (Aircraft*)escortl.get();
	escort2->setPosition(-2, 2, -1);
	escort2->setScale(0.1, 0.1, 0.1);
	escort2->setVelocity(5, mMoveSpeed, 0);
	mPlayerAircraft->attachChild(std::move(escortl));

	std::unique_ptr<bckGround> backgroundSprite(new bckGround(mGame));
	mBackground = (bckGround*)backgroundSprite.get();
	mBackground->setPosition(0, 0, 2.0);
	mBackground->setScale(1.0, 1.0, 1);
	mBackground->setVelocity(0.0, 0.0, -5.0);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<bckGround> backgroundSprite2(new bckGround(mGame));
	mBackground2 = (bckGround*)backgroundSprite2.get();
	mBackground2->setPosition(0, 0, 18);
	mBackground2->setScale(1.0, 1.0, 1);
	mBackground2->setVelocity(0.0, 0.0, -5.0);
	mSceneGraph->attachChild(std::move(backgroundSprite2));

	mSceneGraph->build();
}