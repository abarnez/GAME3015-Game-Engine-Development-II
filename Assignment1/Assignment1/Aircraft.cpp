#include "Aircraft.h"
#include "Game.h"

Aircraft::Aircraft(Type type, Game* game) : Entity(game), mType(type) 
{
	switch (type)
	{
	case (Eagle):
		mSprite = "Eagle";
		break;
	case (Raptor):
		mSprite = "Raptor";
		break;
	default:
		mSprite = "Eagle";
		break;
	}
}

void Aircraft::updateCurrent(const GameTimer& gt)
{	
	Aircraft::check(gt);
	Entity::updateCurrent(gt);				 //Update 						
}

void Aircraft::drawCurrent() const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;
}

void Aircraft::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;
	game->getRenderItems().push_back(std::move(render));
}

unsigned int Aircraft::getCategory() const
{
	switch (mType)
	{
	case Eagle:
		return Category::PlayerAircraft;

	default:
		return Category::EnemyAircraft;
	}
}






































void Aircraft::check(const GameTimer& gt)
{
	XMFLOAT3 pos = this->getWorldPosition(); //get player position
	XMFLOAT3 vel = this->getVelocity();
	if (GetAsyncKeyState(VK_UP)) {
		vel.z = 2;
	}
	else if (GetAsyncKeyState(VK_DOWN)) {
		vel.z = -2;
	}
	else {
		vel.z = 0;
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		vel.x = -2;
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		vel.x = 2;
	}
	else {
		vel.x = 0;
	}
	this->setVelocity(vel);					 //Set the players x velocity to this
	//Entity::updateCurrent(gt);				 //Update 	
}