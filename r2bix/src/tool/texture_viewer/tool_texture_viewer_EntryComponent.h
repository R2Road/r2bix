#pragma once

#include "r2bix/r2bix_component_Component.h"

namespace tool_texture_viewer
{
	class EntryComponent : public r2bix_component::Component<EntryComponent>
	{
	public:
		EntryComponent( r2bix_node::Node& owner_node );

	public:
		void Update( const float delta_time ) override;
	};
}