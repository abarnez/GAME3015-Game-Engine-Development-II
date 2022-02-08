#include "World.h"

World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mWorldBounds(0.f, 0.f, 600.f, 2000.f)
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(-0.f)
{
}

void World::update(const GameTimer& gt)
{
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
	mPlayerAircraft->setVelocity(5, mScrollSpeed);
	mSceneGraph->attachChild(std::move(player));
	
	

	std::unique_ptr<Aircraft> enemy(new Aircraft(Aircraft::Raptor, mGame));
	raptor = (Aircraft*)enemy.get();
	raptor->setPosition(2, 2, -1);
	raptor->setScale(0.1, 0.1, 0.1);
	raptor->setVelocity(5, mScrollSpeed);
	mPlayerAircraft->attachChild(std::move(enemy));
	


	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	raptor2 = (Aircraft*)enemy2.get();
	raptor2->setPosition(-2, 2, -1);
	raptor2->setScale(0.1, 0.1, 0.1);
	raptor2->setVelocity(5, mScrollSpeed);
	mPlayerAircraft->attachChild(std::move(enemy2));

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	mBackground = (SpriteNode*)backgroundSprite.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 2.0);
	mBackground->setScale(1.0, 1.0, 1);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	mSceneGraph->build();
}