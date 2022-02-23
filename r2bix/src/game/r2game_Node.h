#pragma once

#include <list>
#include <memory>

#include "base/r2base_iNode.h"

namespace r2game
{
	enum class eNodeFlag
	{
		Renderable = 1,
	};

	class Node : public r2base::iNode
	{
	protected:
		using ChildContainerT = std::list<r2base::NodeUp>;

		Node( r2base::Director& director );

	public:
		void Update() override {}

		void AddChild( r2base::NodeUp child_node );

	private:
		char mNodeFlags;
		ChildContainerT mChildContainer;
	};
}