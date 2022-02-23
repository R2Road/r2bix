#pragma once

#include <list>
#include <memory>

#include "base/r2base_iNode.h"

namespace r2game
{
	using NodeSp = std::shared_ptr<class Node>;

	class Node : public r2base::iNode
	{
	protected:
		using ChildContainerT = std::list<NodeSp>;

		Node( r2base::Director& director );

	public:
		bool Do() override { return true; }

		void AddChild( NodeSp child_node );

	private:
		ChildContainerT mChildContainer;
	};
}