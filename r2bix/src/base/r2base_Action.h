#pragma once

#include <memory>

namespace r2base
{
	class Node;

	using ActionUp = std::unique_ptr<class Action>;
	class Action
	{
	public:
		Action() {}

		virtual void Enter( r2base::Node& owner_node ) = 0;
		virtual void Update() = 0;
	};
}