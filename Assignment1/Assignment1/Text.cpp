#include "Text.h"
#include "Game.h"

Text::Text(Menu menu, Game* game) : Entity(game), mMenu(menu)
{
	switch (menu)
	{
	case (SplashText):
		mSprite = "SplashText";
		flash = true;
		break;
	case (MenuText1):
		mSprite = "MenuText1";
		break;
	case (MenuText2):
		mSprite = "MenuText2";
		break;
	}
}

void Text::updateCurrent(const GameTimer& gt)
{
	Text::check(gt);
	Entity::updateCurrent(gt);
	/*XMFLOAT3 pos;
	pos.x = mParent->getWorldPosition().x;
	pos.y = mParent->getWorldPosition().y;
	pos.z = mParent->getWorldPosition().z;
	this->setPosition(pos.x, pos.y, pos.z);*/
}

void Text::drawCurrent() const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;
}

void Text::buildCurrent()
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

void Text::check(const GameTimer& gt) 
{
	if (GetAsyncKeyState('Q'))
		this->setPosition(0.f, -1.f, 0.f);
	


	if (GetAsyncKeyState('C')) 
	{
		show = false;
	}
	if (GetAsyncKeyState('P') & 0x8000) 
	{

		show = true;

	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_UP))
	{
		this->setPosition(0.f, -5.f, 0.f);
	}
	if (show) 
	{
		if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_UP)) 
		{
			this->setPosition(1, 2.55, -3);
			show = false;
		}
	}
}