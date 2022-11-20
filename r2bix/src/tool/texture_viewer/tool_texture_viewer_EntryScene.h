#pragma once

#include <memory>

#include "r2bix/r2bix_node_SceneNode.h"

namespace tool_texture_viewer
{
	class EntryScene : public r2bix_node::SceneNode
	{
	private:
		EntryScene( r2bix::Director& director );

	public:
		static const char* const GetTitle() { return "Texture Viewer"; }
		static r2bix_node::SceneNodeUp Create( r2bix::Director& director );

	public:
		void Update( const float delta_time ) override;
	};
}