#pragma once

#include <memory>

#include "r2bix_node_Node.h"

namespace tool_texture_editor
{
	class EntryScene : public r2bix_node::Node
	{
	private:
		EntryScene( r2bix::Director& director );

	public:
		static const char* const GetTitle() { return "Texture Editor"; }
		static r2bix_node::NodeUp Create( r2bix::Director& director );

	private:
		bool Init() override;
	};
}