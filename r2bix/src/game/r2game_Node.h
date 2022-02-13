#pragma once

#include "base/r2base_iNode.h"

namespace r2game
{
	class Node : public r2base::iNode
	{
	protected:
		Node( r2base::Director& director );

	public:
		bool Do() override { return true; }
	};
}