#pragma once

#include <memory>

namespace r2base
{
	using NodeUp = std::unique_ptr<class Node>;

	class Director;
}

namespace r2test
{
	class RootScene
	{
	private:
		RootScene() = delete;

	public:
		static const char* GetTitle() { return "Test"; }
		static r2base::NodeUp Create( r2base::Director& director );
	};
}