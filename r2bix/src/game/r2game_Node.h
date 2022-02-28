#pragma once

#include "base/r2base_Node.h"

namespace r2game
{
	enum class eNodeFlag
	{
		Renderable = 1,
	};

	class Node : public r2base::Node
	{
	protected:
		Node( r2base::Director& director );

	public:
		void Update() override {}

	private:
		char mNodeFlags;
	};
}