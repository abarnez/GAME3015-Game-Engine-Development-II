#include "Pause.h"
#include "Game.h"
#include <iostream>
Pause::Pause(Game* game) : Entity(game)
{
}

void Pause::updateCurrent(const GameTimer& gt)
{
	if (GetAsyncKeyState('C')) {
		show = false;
	}
	if (GetAsyncKeyState('P') & 0x8000) {
	
		show = true;
		
	}
	if (GetAsyncKeyState(VK_BACK)) {
		show = false;
	}
	if (show) {
		this->setPosition(0, 2.6, -2);
		
	}
	if (!show) {
		this->setPosition(0.f, -5.f, 0.f);
	}
	Entity::updateCurrent(gt);
	Pause::check(gt);

}

void Pause::drawCurrent() const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;
}

void Pause::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(1.0f, 1.4f, 1.0f));
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()["PauseTex"].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;
	game->getRenderItems().push_back(std::move(render));
}

void Pause::check(const GameTimer& gt) {

	
	
		


}