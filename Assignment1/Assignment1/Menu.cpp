#include "Menu.h"
#include "Game.h"
#include <iostream>
Menu::Menu(Game* game) : Entity(game)
{
}

void Menu::updateCurrent(const GameTimer& gt)
{
	if (GetAsyncKeyState('C')) {
		show = false;
	}
	if (GetAsyncKeyState('P') & 0x8000) {

		show = true;

	}
	if (GetAsyncKeyState(VK_RETURN)) {
		this->setPosition(0.f, -5.f, 0.f);
	}
	if (show) {
		if (GetAsyncKeyState(VK_BACK)) {
			this->setPosition(1, 2.55, -3);
		}
	}
	Entity::updateCurrent(gt);
	Menu::check(gt);

}

void Menu::drawCurrent() const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;
}

void Menu::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(1.0f, 1.4f, 1.0f));
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()["MenuTex"].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;
	game->getRenderItems().push_back(std::move(render));
}

void Menu::check(const GameTimer& gt) {






}