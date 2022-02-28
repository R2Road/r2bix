#pragma once

#include <memory>

namespace r2base
{
	using NodeUp = std::unique_ptr<class Node>;

	class Director;
}

namespace r2test
{
	class RenderableScene
	{
	private:
		RenderableScene() = delete;

	public:
		static const char* GetTitle() { return "Renderable"; }
		static r2base::NodeUp Create( r2base::Director& director );
	};
}