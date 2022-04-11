#include "World.h"

World::World(Game* game)	: mSceneGraph(new SceneNode(game))	, mGame(game)	, mPlayerAircraft(nullptr)	, mBackground(nullptr)	, mBackground2(nullptr)
	, mWorldBounds(0.f, 0.f, 600.f, 2000.f)	, mSpawnPosition(0.f, 0.f)	, mMoveSpeed(-0.f) , mSplashScreen(nullptr)
{
}

CommandQueue& World::getCommandQueue() {
	return mCommandQueue;
}


void World::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);

	// Forward commands to the scene graph
	while (!mCommandQueue.isEmpty())
		mSceneGraph->onCommand(mCommandQueue.pop(), gt); //not sure if this is correct



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

	std::unique_ptr<SplashScreen> dSplashScreen(new SplashScreen(mGame));
	mSplashScreen = (SplashScreen*)dSplashScreen.get();
	mSplashScreen->setPosition(0, 2.6, -3);
	mSplashScreen->setScale(1.0, 1.0, 1);
	mSplashScreen->setVelocity(0.0, 0.0, 0.0);
	mSceneGraph->attachChild(std::move(dSplashScreen));

	std::unique_ptr<Text> texts(new Text(Text::SplashText, mGame));
	mText = (Text*)texts.get();
	mText->setPosition(0, 2.7, 0);
	mText->setScale(0.5, 0.5, 0.05);
	mText->setVelocity(0.0, 0.0, 0.0);
	mSceneGraph->attachChild(std::move(texts));

	std::unique_ptr<Pause> gPause(new Pause(mGame));
	mPause = (Pause*)gPause.get();
	mPause->setPosition(0, -1.0, 0);
	mPause->setScale(0.9, 1.0, 1.0);
	mPause->setVelocity(0.0, 0.0, 0.0);
	mSceneGraph->attachChild(std::move(gPause));

	std::unique_ptr<Menu> gMenu(new Menu(mGame));
	mMenu = (Menu*)gMenu.get();
	mMenu->setPosition(1, 2.55, -3);
	mMenu->setScale(1.0, 1.0, 1.0);
	mMenu->setVelocity(0.0, 0.0, 0.0);
	mSceneGraph->attachChild(std::move(gMenu));

	std::unique_ptr<Text> playText(new Text(Text::MenuText1, mGame));
	mText1 = (Text*)playText.get();
	mText1->setPosition(0, 2.63, 0);
	mText1->setScale(0.5, 0.5, 0.5);
	mText1->setVelocity(0.0, 0.0, 0.0);
	mSceneGraph->attachChild(std::move(playText));

	std::unique_ptr<Text> pauseText(new Text(Text::MenuText2, mGame));
	mText2 = (Text*)pauseText.get();
	mText2->setPosition(0, 2.63, 0);
	mText2->setScale(0.5, 0.5, 0.5);
	mText2->setVelocity(0.0, 0.0, 0.0);
	mSceneGraph->attachChild(std::move(pauseText));

	mSceneGraph->build();
}