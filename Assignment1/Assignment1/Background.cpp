#include "Background.h"
#include "Game.h"

bckGround::bckGround(Game* game) : Entity(game)
{
}

void bckGround::updateCurrent(const GameTimer& gt)
{
	XMFLOAT3 pos1 = this->getWorldPosition();	//Get Position of the background
	if (pos1.z < -17.5) {						//Check the Z position to see if it has gone off screen
		this->setPosition(0, 0, 18.5);			//If it has reset its position to the top of the screen
	}
	Entity::updateCurrent(gt);
}

void bckGround::drawCurrent() const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;
}

void bckGround::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(10.0f, 10.0f, 10.0f));
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()["Desert"].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;
	game->getRenderItems().push_back(std::move(render));
}