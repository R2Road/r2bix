#pragma once

#include <memory>

namespace r2base
{
	using NodeUp = std::unique_ptr<class iNode>;

	class Director;
}

namespace r2game
{
	class RootScene
	{
	private:
		RootScene() = delete;

	public:
		static const char* GetTitle() { return "Game"; }
		static r2base::NodeUp Create( r2base::Director& director );
	};
}