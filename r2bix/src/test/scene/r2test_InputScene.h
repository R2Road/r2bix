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
	class InputScene
	{
	private:
		InputScene() = delete;

	public:
		static const char* GetTitle() { return "Input"; }
		static r2node::SceneNodeUp Create( r2base::Director& director );
	};
}