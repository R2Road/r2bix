#pragma once

#include <memory>

namespace r2base
{
	class Director;
}

namespace r2node
{
	using SceneNodeUp = std::unique_ptr<class SceneNode>;
}

namespace r2research
{
	class RootScene
	{
	private:
		RootScene() = delete;

	public:
		static const char* GetTitle() { return "Research"; }
		static r2node::SceneNodeUp Create( r2base::Director& director );
	};
}