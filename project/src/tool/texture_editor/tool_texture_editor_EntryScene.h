#pragma once

#include "r2bix_node_Node.h"

namespace tool_texture_editor
{
	class EntryScene
	{
	private:
		EntryScene() = delete;

	public:
		static const char* const GetTitle() { return "Texture Editor"; }
		static r2bix_node::NodeUp Create( r2bix::Director& director );
	};
}