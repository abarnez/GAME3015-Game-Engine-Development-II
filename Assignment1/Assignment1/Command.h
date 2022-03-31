
#pragma once
#include "Category.h"

#include "Common/d3dApp.h"
#include <functional>
#include <cassert>

class SceneNode;

struct Command
{
	Command();

	std::function<void(SceneNode&, GameTimer& gt)>	action;
	unsigned int								category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, GameTimer& gt)> derivedAction(Function fn)
{
	return [=](SceneNode& node, GameTimer& gt)
	{
		// Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		// Downcast node and invoke function on it
		fn(static_cast<GameObject&>(node), gt);
	};
}
