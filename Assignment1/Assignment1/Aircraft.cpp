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
	XMFLOAT3 pos = this->getWorldPosition(); //get player position
	XMFLOAT3 vel = this->getVelocity();		 //get player velocity
	if (pos.x >= 6 || pos.x <= -6) {		 //once they get to either side of the screen 
		vel.x = -vel.x;						 //flip the velocity from -/+ or +/-

	}
	this->setVelocity(vel);					 //Set the players x velocity to this
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

