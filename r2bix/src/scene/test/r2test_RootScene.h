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

namespace r2test
{
	class RootScene
	{
	private:
		RootScene() = delete;

	public:
		static const char* GetTitle() { return "Test"; }
		static r2node::SceneNodeUp Create( r2base::Director& director );
	};
}