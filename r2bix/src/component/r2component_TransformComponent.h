#pragma once

#include "base/r2base_iComponent.h"

namespace r2component
{
	class TransformComponent : public r2base::iComponent
	{
	private:
		TransformComponent( r2base::Node& owner_node ) : r2base::iComponent( owner_node )
		{}

	public:
		static r2base::ComponentUp Create( r2base::Node& owner_node );

		bool Init() override { return true; }
		void Update() override {}
	};
}