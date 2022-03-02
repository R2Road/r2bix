#pragma once

#include "base/r2base_Node.h"

namespace r2base
{
	class Director;
}

namespace r2game
{
	class Scene : public r2base::Node
	{
	public:
		Scene( r2base::Director& director );

		void Update() override;
	};
}