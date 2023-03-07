#pragma once
#include "Category.h"

#include "../../Common/d3dApp.h"


#include <functional>
#include <cassert>

class SceneNode;
/// This struct is use as a template to create commands 
struct Command
{
	Command();

	std::function<void(SceneNode&, const GameTimer&)> action;
	unsigned int category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, const GameTimer&)> derivedAction(Function fn)
{
	return [=](SceneNode& node, const GameTimer& gt)
	{
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		fn(static_cast<GameObject&>(node), gt);
	};
}

