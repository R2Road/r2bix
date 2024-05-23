#pragma once

#include "r2bix_node_Node.h"

namespace tool_texture_editor
{
	class EditorScene
	{
	private:
		EditorScene() = delete;

	public:
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}