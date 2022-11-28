#pragma once

#include <memory>

#include "r2bix/r2bix_node_SceneNode.h"

namespace tool_texture_viewer
{
	class ViewerScene : public r2bix_node::SceneNode
	{
	private:
		ViewerScene() = delete;

	public:
		static r2bix_node::SceneNodeUp Create( r2bix::Director& director );
	};
}