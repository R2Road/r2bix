#pragma once

#include "base/r2base_Node.h"

namespace r2base
{
	class Director;
}

namespace r2node
{
	using SceneNodeUp = std::unique_ptr<class SceneNode>;

	class SceneNode : public r2base::Node
	{
	public:
		SceneNode( r2base::Director& director );

		void Update() override;
	};
}