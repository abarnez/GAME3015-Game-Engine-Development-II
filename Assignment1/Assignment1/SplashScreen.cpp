#include "SplashScreen.h"
#include "Game.h"
#include <iostream>
SplashScreen::SplashScreen(Game* game) : Entity(game)
{
}

void SplashScreen::updateCurrent(const GameTimer& gt)
{
	Entity::updateCurrent(gt);
	SplashScreen::check(gt);	
}

void SplashScreen::drawCurrent() const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;
}

void SplashScreen::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(1.0f, 1.4f, 1.0f));
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()["Splash"].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;
	game->getRenderItems().push_back(std::move(render));
}






void SplashScreen::check(const GameTimer& gt) {
	
	if(GetAsyncKeyState('Q'))
	this->setPosition(0.f, -1.f, 0.f);	
}