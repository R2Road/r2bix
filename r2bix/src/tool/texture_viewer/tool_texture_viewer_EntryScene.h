#pragma once

#include <memory>

namespace r2bix
{
	class Director;
}

namespace r2bix_node
{
	using SceneNodeUp = std::unique_ptr<class SceneNode>;
}

namespace tool_texture_viewer
{
	class EntryScene
	{
	private:
		EntryScene() = delete;

	public:
		static const char* const GetTitle() { return "Texture Viewer"; }
		static r2bix_node::SceneNodeUp Create( r2bix::Director& director );
	};
}