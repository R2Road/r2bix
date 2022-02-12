#pragma once

#include <memory>

namespace r2
{
	using NodeUp = std::unique_ptr<class iNode>;

	class Director;
}

namespace r2test
{
	class RootMenu
	{
	private:
		RootMenu() = delete;

	public:
		static const char* GetTitle() { return "Test"; }
		static r2::NodeUp Create( r2::Director& director );
	};
}